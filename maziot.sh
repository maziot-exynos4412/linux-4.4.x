#!/bin/sh

make -j8 uImage LOADADDR=0x40008000

echo ""
echo "\033[31m>>>>>>>>>>>>>>>>>>>>>>>>>>>> make uImage successful <<<<<<<<<<<<<<<<<<<<<<<<<<<<\033[0m"
echo ""

make dtbs

echo ""
echo "\033[31m>>>>>>>>>>>>>>>>>>>>>>>>>>>>> make dtbs successful <<<<<<<<<<<<<<<<<<<<<<<<<<<<<\033[0m"
echo ""

cp -av arch/arm/boot/dts/exynos4412-tiny4412.dtb ./
cp -av arch/arm/boot/uImage ./

echo ""
echo "\033[31m>>>>>>>>>>>>>>>>>>>>>>>> copy uImage and dtb successful <<<<<<<<<<<<<<<<<<<<<<<<\033[0m"
echo ""

