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

MODULE_AUTHOR("sel-melc");
MODULE_DESCRIPTION("Keylogger");
MODULE_LICENSE("GPL");

#define INTRA_LOGIN "sel-melc"

char *log_buffer = NULL;

static ssize_t handle_read(struct file *file, char __user *to, size_t size, loff_t *_offset)
{
	return simple_read_from_buffer(to, size, _offset, INTRA_LOGIN, sizeof(INTRA_LOGIN) - 1);
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
}

module_init(init);
module_exit(cleanup);
