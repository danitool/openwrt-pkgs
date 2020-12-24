/*
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static int proc_dump_cp15_read(struct seq_file *p, void *v)
{
	unsigned int value;

	asm volatile("mrc p15, 0, %0, c0, c0, 0": "=r"(value));
	seq_printf(p, "Main ID: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c0, 1": "=r"(value));
	seq_printf(p, "Cache Type: 0x%08x\n", value);

#ifdef CONFIG_CPU_V7
	asm volatile("mrc p15, 0, %0, c0, c0, 2": "=r"(value));
	seq_printf(p, "TCM Type: 0x%08x\n", value);
#endif

	asm volatile("mrc p15, 0, %0, c0, c0, 3": "=r"(value));
	seq_printf(p, "TLB Type: 0x%08x\n", value);

#ifdef CONFIG_CPU_V7
	asm volatile("mrc p15, 0, %0, c0, c0, 5": "=r"(value));
	seq_printf(p, "Microprocessor ID: 0x%08x\n", value);
#endif

	asm volatile("mrc p15, 0, %0, c0, c1, 0": "=r"(value));
	seq_printf(p, "Processor Feature 0: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c1, 1": "=r"(value));
	seq_printf(p, "Processor Feature 1: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c1, 2": "=r"(value));
	seq_printf(p, "Debug Feature 0: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c1, 3": "=r"(value));
	seq_printf(p, "Auxiliary Feature 0: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c1, 4": "=r"(value));
	seq_printf(p, "Memory Model Feature 0: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c1, 5": "=r"(value));
	seq_printf(p, "Memory Model Feature 1: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c1, 6": "=r"(value));
	seq_printf(p, "Memory Model Feature 2: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c1, 7": "=r"(value));
	seq_printf(p, "Memory Model Feature 3: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c2, 0": "=r"(value));
	seq_printf(p, "Set Attribute 0: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c2, 1": "=r"(value));
	seq_printf(p, "Set Attribute 1: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c2, 2": "=r"(value));
	seq_printf(p, "Set Attribute 2: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c2, 3": "=r"(value));
	seq_printf(p, "Set Attribute 3: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c2, 4": "=r"(value));
	seq_printf(p, "Set Attribute 4: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c0, c2, 5": "=r"(value));
	seq_printf(p, "Set Attribute 5: 0x%08x\n", value);
#ifdef CONFIG_CPU_V7
	asm volatile("mrc p15, 1, %0, c0, c0, 0": "=r"(value));
	seq_printf(p, "Current Cache Size ID: 0x%08x\n", value);

	asm volatile("mrc p15, 1, %0, c0, c0, 1": "=r"(value));
	seq_printf(p, "Current Cache Level ID: 0x%08x\n", value);

	asm volatile("mrc p15, 1, %0, c0, c0, 7": "=r"(value));
	seq_printf(p, "Silicon ID: 0x%08x\n", value);

	asm volatile("mrc p15, 2, %0, c0, c0, 0": "=r"(value));
	seq_printf(p, "Cache Size Selection: 0x%08x\n", value);

#endif
	asm volatile("mrc p15, 0, %0, c1, c0, 0": "=r"(value));
	seq_printf(p, "Control : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c1, c0, 1": "=r"(value));
	seq_printf(p, "Auxiliary Control : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c1, c0, 2": "=r"(value));
	seq_printf(p, "Coprocessor Access Control : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c1, c1, 0": "=r"(value));
	seq_printf(p, "Secure Configuration : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c2, c0, 0": "=r"(value));
	seq_printf(p, "Translation Table Base 0 : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c2, c0, 1": "=r"(value));
	seq_printf(p, "Translation Table Base 1 : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c2, c0, 2": "=r"(value));
	seq_printf(p, "Translation Table Control : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c3, c0, 0": "=r"(value));
	seq_printf(p, "Domain Access Control : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c5, c0, 0": "=r"(value));
	seq_printf(p, "Data Fault Status : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c5, c0, 1": "=r"(value));
	seq_printf(p, "Instruction Fault Status : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c6, c0, 0": "=r"(value));
	seq_printf(p, "Data Fault Address : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c6, c0, 1": "=r"(value));
	seq_printf(p, "Watchpoint Fault Address : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c6, c0, 2": "=r"(value));
	seq_printf(p, "Instruction Fault Address : 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c7, c10, 6": "=r"(value));
	seq_printf(p, "Cache Dirty Status: 0x%08x\n", value);

	asm volatile("mrc p15, 1, %0, c15, c1, 0": "=r"(value));
	seq_printf(p, "Auxiliary Debug Modes Control 0: 0x%08x\n", value);

	asm volatile("mrc p15, 1, %0, c15, c1, 1": "=r"(value));
	seq_printf(p, "Auxiliary Debug Modes Control 1: 0x%08x\n", value);

#if 1
	asm volatile("mrc p15, 1, %0, c15, c1, 0": "=r"(value));
	seq_printf(p, "Control Configuration: 0x%08x\n", value);
	seq_printf(p, "    Write Buffer Coalescing\t: %s\n", (value & (1 << 8)) ?
		     "Enabled" : "Disabled");
	if (value & (1 << 8))
		seq_printf(p, "    WB WAIT CYC\t: 0x%x\n", (value >> 9) & 0x7);

	seq_printf(p, "    Coprocessor dual issue \t: %s\n", (value & (1 << 15)) ?
		     "Disabled" : "Enabled");

	seq_printf(p, "    L2 write allocate\t: %s\n", (value & (1 << 28)) ?
		     "Enabled" : "Disabled");

	seq_printf(p, "    Streaming\t: %s\n", (value & (1 << 29)) ?
		     "Enabled" : "Disabled");
#endif
	asm volatile("mrc p15, 1, %0, c15, c12, 0": "=r"(value));
	seq_printf(p, "CPU ID Code Extension: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c9, c14, 0": "=r"(value));
	seq_printf(p, "User mode access for PMC registers: %s\n", (value & 1) ?
		     "Enabled" : "Disabled");
	asm volatile("mrc p15, 0, %0, c10, c2, 0": "=r"(value));
	seq_printf(p, "Memory Attribute PRRR: 0x%08x\n", value);

	asm volatile("mrc p15, 0, %0, c10, c2, 1": "=r"(value));
	seq_printf(p, "Memory Attribute NMRR: 0x%08x\n", value);

	asm volatile("mrc p15, 1, %0, c15, c1, 2": "=r"(value));
	seq_printf(p, "Auxiliary Debug Modes Control 2: 0x%08x\n", value);

	asm volatile("mrc p15, 1, %0, c15, c2, 0": "=r"(value));
	seq_printf(p, "Auxiliary Functional Modes Control 0: 0x%08x\n", value);

	asm volatile("mrc p15, 1, %0, c15, c2, 1": "=r"(value));
	seq_printf(p, "Auxiliary Functional Modes Control 1: 0x%08x\n", value);

	return 0;
}

static int proc_mv_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_dump_cp15_read, NULL);
}

static const struct file_operations mv_fops = {
	.open      = proc_mv_open,
	.read      = seq_read,
	.llseek    = seq_lseek,
	.release   = single_release,
};

static int __init dump_init_module(void)
{
#ifdef CONFIG_PROC_FS
	struct proc_dir_entry *res;
	res = proc_create("mv_dump_cp15", S_IRUSR, NULL, &mv_fops);
	if (!res)
		return -ENOMEM;
#endif

	return 0;
}

static void __exit dump_cleanup_module(void)
{
	remove_proc_entry("mv_dump_cp15", NULL);
}

module_init(dump_init_module);
module_exit(dump_cleanup_module);

MODULE_AUTHOR("Saeed Bishara, Daniel González Cabanelas <dgcbueu@gmail.com>");
MODULE_LICENSE("GPL");
