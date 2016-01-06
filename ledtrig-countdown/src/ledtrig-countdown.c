/*
 * LED Kernel Countdown Trigger
 *
 * Author: Daniel González <dgcbueu@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/ctype.h>
#include <linux/leds.h>
#include "leds.h"


static ulong delay = 0;
static struct timer_list timer_countdown;

static void countdown_func(unsigned long data)
{
	struct led_classdev *led_cdev = (struct led_classdev *) data;
	led_brightness_set(led_cdev, LED_OFF);
}

static ssize_t countdown_show(struct device *dev, 
			      struct device_attribute *attr, char *buf)
{
	sprintf(buf, "%lu\n", delay);

	return strlen(buf) + 1;
}

static ssize_t countdown_store(struct device *dev,
			       struct device_attribute *attr, const char *buf, size_t size)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	int ret = -EINVAL;
	char *after;
	unsigned long state = simple_strtoul(buf, &after, 10);
	size_t count = after - buf;

	if (isspace(*after))
		count++;

	if (count == size) {
		delay = state;
		ret = count;
	}

	if (delay != 0) {
		led_set_brightness(led_cdev, led_cdev->max_brightness);
		mod_timer(&timer_countdown, jiffies + msecs_to_jiffies(delay));
	}

	return ret;
}

static DEVICE_ATTR(countdown, 0644, countdown_show, countdown_store);

static void countdown_trig_activate(struct led_classdev *led_cdev)
{
	int rc;

	led_cdev->trigger_data = NULL;

	setup_timer(&timer_countdown, countdown_func, (unsigned long) led_cdev);
	rc = device_create_file(led_cdev->dev, &dev_attr_countdown);
	if (rc)
		return;

	led_cdev->trigger_data = (void *)1;

	return;
}

static void countdown_trig_deactivate(struct led_classdev *led_cdev)
{
	if (led_cdev->trigger_data) {
		device_remove_file(led_cdev->dev, &dev_attr_countdown);
	}

	/* Stop countdown */
	del_timer_sync(&timer_countdown);
	led_brightness_set(led_cdev, LED_OFF);
}

static struct led_trigger countdown_led_trigger = {
	.name     = "countdown",
	.activate = countdown_trig_activate,
	.deactivate = countdown_trig_deactivate,
};

static int __init countdown_trig_init(void)
{
	return led_trigger_register(&countdown_led_trigger);
}

static void __exit countdown_trig_exit(void)
{
	led_trigger_unregister(&countdown_led_trigger);
}

module_init(countdown_trig_init);
module_exit(countdown_trig_exit);

MODULE_AUTHOR("Daniel Gonzalez <dgcbueu@gmail.com>");
MODULE_DESCRIPTION("Countdown LED trigger");
MODULE_LICENSE("GPL");
 
