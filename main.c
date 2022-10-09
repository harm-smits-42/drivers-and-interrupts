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
#include <string.h>

MODULE_AUTHOR("sel-melc");
MODULE_DESCRIPTION("Keylogger");
MODULE_LICENSE("GPL");

#define INTRA_LOGIN "sel-melc"

char *log_buffer = NULL;

/*
*  Adds a new entry to the log_buffer.
*/
static int add_new_entry(char *entry)
{
	char *tmp_buff;
	if (!(tmp_buff = vmalloc(log_buffer ? strlen(entry) + strlen(log_buffer) + 1 : strlen(entry) + 1)))
	{
		printk(KERN_WARN "Failed to allocate memory for new log entry\n");
		return (1);
	}
	tmp_buff[0] = '\0';
	if (log_buffer)
		strcpy(tmp_buff, log_buffer);
	strcat(tmp_buff, entry);
	if (log_buffer)
		vfree(log_buffer);
	log_buffer = tmp_buff;
	return (0);
}

static ssize_t handle_read(struct file *file, char __user *to, size_t size, loff_t *_offset)
{
	if (!log_buffer)
		return (0);
	return simple_read_from_buffer(to, size, _offset, log_buffer, strlen(log_buffer));
}

static ssize_t handle_write(struct file *file, const char __user *from, size_t size, loff_t *_offset)
{
	static char buf[sizeof(INTRA_LOGIN)];
	ssize_t ret;

	if (size != sizeof(INTRA_LOGIN) - 1)
		return -EINVAL;
	ret = copy_from_user(buf, from, sizeof(INTRA_LOGIN) - 1);

	if (ret || memcmp(buf, INTRA_LOGIN, sizeof(INTRA_LOGIN) - 1))
		return -EINVAL;

	return sizeof(INTRA_LOGIN) - 1;
}

static struct file_operations fops = {
	.read = &handle_read,
	.write = &handle_write,
};

static struct miscdevice misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "keylogger",
	.fops = &fops,
	.mode = 0666,
};

static int __init init(void)
{
	misc_register(&misc_dev);
	return (0);
}

static void __exit cleanup(void)
{
	misc_deregister(&misc_dev);
	if (log_buffer)
		vfree(log_buffer);
}

module_init(init);
module_exit(cleanup);
