/*
 * Dummy IRQ handler driver.
 *
 * This module only registers itself as a handler that is specified to it
 * by the 'irq' parameter.
 *
 * The sole purpose of this module is to help with debugging of systems on
 * which spurious IRQs would happen on disabled IRQ vector.
 *
 * Copyright (C) 2013 Jiri Kosina
 *               2016 Daniel González
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>

static int irq = -1;
static int gpio = -1;

static irqreturn_t dummy_interrupt(int irq, void *dev_id)
{
	static int count = 0;

	count++;
	printk(KERN_INFO "dummy-irq: %d interrupt occured on IRQ %d\n",
				count, irq);

	return IRQ_HANDLED;
}

static int __init dummy_irq_init(void)
{
	if (irq < 0 && gpio < 0) {
		printk(KERN_ERR "dummy-irq: no IRQ or GPIO given. Use irq=N or gpio=N\n");
		return -EINVAL;
	}

	if ( gpio >= 0) {
		irq = gpio_to_irq(gpio);
			if (irq < 0) {
				printk(KERN_ERR "dummy-irq: no IRQ number for GPIO%d\n", gpio);
				return -EINVAL;
			}
	}

	if (request_irq(irq, &dummy_interrupt, IRQF_SHARED, "dummy_irq", &irq)) {
		printk(KERN_ERR "dummy-irq: cannot register IRQ %d\n", irq);
		return -EINVAL;
	}
	printk(KERN_INFO "dummy-irq: registered for IRQ %d\n", irq);
	return 0;
}

static void __exit dummy_irq_exit(void)
{
	printk(KERN_INFO "dummy-irq unloaded\n");
	free_irq(irq, &irq);
}

module_init(dummy_irq_init);
module_exit(dummy_irq_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jiri Kosina");
module_param(irq, uint, 0444);
module_param(gpio, uint, 0444);
MODULE_PARM_DESC(irq, "The IRQ to register for");
MODULE_PARM_DESC(gpio, "The GPIO to register its IRQ for");
