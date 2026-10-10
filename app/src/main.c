#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    printk("SmartHome firmware booted\n");
    return 0;
}
