#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/delay.h>

#define log(fmt, arg...) printk(KERN_INFO "[Maziot][leds][%s][%d] "fmt"\n", __func__, __LINE__, ##arg)

struct pinctrl *pctrl;
struct pinctrl_state *sleep_pstate;
struct pinctrl_state *active_pstate;

static int maziot_leds_probe(struct platform_device *pdev) 
{
        struct device *dev = &pdev->dev;

        log("enter");
        log("leds dts node's name = %s", dev->of_node->name);

        pctrl = devm_pinctrl_get(dev);
        sleep_pstate = pinctrl_lookup_state(pctrl, "gpio_sleep");
        active_pstate = pinctrl_lookup_state(pctrl, "gpio_active");

        pinctrl_select_state(pctrl, active_pstate);

        log("exit");

        return 0;
}

static int maziot_leds_remove(struct platform_device *pdev)
{
        log("enter");
        return 0;
}

static const struct of_device_id maziot_leds_dt_ids[] = {
        {.compatible = "maziot,leds",},
        {},
};

MODULE_DEVICE_TABLE(of, gpio_demo_dt_ids);

static struct platform_driver maziot_leds_driver = {
        .probe	= maziot_leds_probe,
        .remove	= maziot_leds_remove,
        .driver	= {
                .name           = "maziot_leds",
                .of_match_table	= of_match_ptr(maziot_leds_dt_ids),
        },
};

static int __init maziot_leds_init(void)
{
        platform_driver_register(&maziot_leds_driver);
        return 0;
}

static void __exit maziot_leds_exit(void)
{
        platform_driver_unregister(&maziot_leds_driver);
}

module_init(maziot_leds_init);
module_exit(maziot_leds_exit);

MODULE_LICENSE("GPL");