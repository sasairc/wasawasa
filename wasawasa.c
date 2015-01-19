/*
 * wasawasa - Baby, please kernel module. (BPKM)
 * 
 * Copyright © 2014 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.Hocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */
 
#define MODNAME "wasawasa"
#define CHAR_MAJOR      254
#define CHAR_MINOR      1

#include <linux/semaphore.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <asm/string.h>

MODULE_LICENSE("WTFPL");
MODULE_AUTHOR("sasairc");

static struct cdev cdev;
static struct semaphore cdev_sem;

static int open_chardev(struct inode *inode, struct file *file)
{
        return 0;
}

static int release_chardev(struct inode *inode, struct file *file)
{
        return 0;
}

static ssize_t read_chardev(struct file *file, char *buf, size_t count, loff_t *offset)
{
        char *str = "わさわさ";

        down_interruptible(&cdev_sem);
        copy_to_user(buf, str, strlen(str));

        *offset += strlen(str);
        up(&cdev_sem);
        return strlen(str);
}

static struct file_operations cdev_fops = {
        .owner  = THIS_MODULE,
        .open   = open_chardev,
        .read   = read_chardev,
        .release = release_chardev,
};

static int __init init_chardev(void)
{
        int ret;
        dev_t dev;

        dev = MKDEV(CHAR_MAJOR, 0);
        cdev_init(&cdev, &cdev_fops);

        ret = cdev_add(&cdev, dev, CHAR_MINOR);
        if (ret < 0) {
                printk(KERN_WARNING "%s: cdev_add() failure.\n", MODNAME);
                return ret;
        }

        sema_init(&cdev_sem, 1);

        return 0;
}

static void __exit exit_chardev(void)
{
        dev_t dev;

        dev = MKDEV(CHAR_MAJOR, 0);
        cdev_del(&cdev);
        unregister_chrdev_region(dev, CHAR_MINOR);
}

module_init(init_chardev);
module_exit(exit_chardev);
