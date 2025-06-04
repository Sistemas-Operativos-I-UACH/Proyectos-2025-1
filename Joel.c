//Joel.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>



MODULE_AUTHOR("KEVIN OLIVAS");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MODULO JOEL");
MODULE_VERSION("FINAL");


#define DEVICE_NAME "MODULO-JOEL"
#define BUFFER_SIZE 1024

static int major_number;
static int device_open_count = 0;
static char device_buffer[BUFFER_SIZE];
static int exit = 0;


static int joel_device_open(struct inode *inode, struct file *file);
static int joel_device_close(struct inode *inode, struct file *file);
static ssize_t joel_device_read(struct file *filep, char *buffer, size_t len, loff_t *offset);
static ssize_t joel_device_write(struct file *filep, const char *buffer, size_t len, loff_t *offset);

// Define file operations structure
static struct file_operations fops = {
    .open = joel_device_open,
    .release = joel_device_close,
    .read = joel_device_read,
    .write = joel_device_write
};


// Open function
static int joel_device_open(struct inode *inode, struct file *file) {
    device_open_count++;
    printk(KERN_INFO "Se abrió el dispositivo: %s\n\n\n", DEVICE_NAME);
    printk(KERN_INFO "Escapemos de la oscuridad, y volemos hacía el mas allá: %s\n\n\n", device_open_count);
    printk(KERN_INFO "Letra del OP de Dan Da Dan\n\n\n\n");
    return 0;
}


// Close function
static int joel_device_close(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Cerrando disponsitivo Dan Da Dan\n");
    return 0;
}


static int __init joel_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "simple_module: Failed to register a major number\n");
        return major_number;
    }

    printk(KERN_INFO "Cargando Módulo joel!\n\n\n %d",major_number);
    printk(KERN_INFO "Escapemos de la oscuridad, y volemos hacía el mas allá\n\n\n");
    return 0;
}

static void __exit joel_exit(void) {
    printk(KERN_INFO "Un gusto verlos aqui. hasta la prox!!!\n\n\n");
}


static ssize_t joel_device_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int errors = 0;
    printk(KERN_INFO "Entrando a joel_device_read\n");
    char *message = "Dandadan, dandadan, dandadan, dandadan, dandadan\n";
    int message_len = strlen(message);

    if (exit == 0) {
        exit = 1;
        errors = copy_to_user(buffer, message, message_len);
    } else {
        exit = 0;
       return 0;
    }

    if (errors == 0) {
        return message_len;
    } else {
        exit = 0;
        return -EFAULT;
    }
}

/* Device write function */
static ssize_t joel_device_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
    printk(KERN_INFO "Entrando a write\n");
    int bytes_written = 0;
    if (*offset >= BUFFER_SIZE) return 0;

    if (len + *offset > BUFFER_SIZE) len = BUFFER_SIZE - *offset;

    if (copy_from_user(device_buffer + *offset, buffer, len) != 0) return -EFAULT;

    *offset += len;
    bytes_written = len;
    printk(KERN_INFO "chardev: Received %d bytes from the user\n", bytes_written);
    printk(KERN_INFO "chardev: Received %s from the user\n", device_buffer);
    printk(KERN_INFO "Saliendo a write\n");
    return bytes_written;
}
module_init(joel_init);
module_exit(joel_exit);
