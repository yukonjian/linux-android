"reg"是寄存器，格式是"<address,length>"，作为平台内存资源；
reg = <0x0 0x1000000 0x0 0x300000 0x0 0x1c70000 0x0 0xfff 0x0 0x1c71000 0x0 0xfff>
g_disp_drv.reg_base[DISP_MOD_DSI0] = (uintptr_t __force)of_iomap(pdev->dev.of_node, counter);
if (!g_disp_drv.reg_base[DISP_MOD_DSI0]) {
  dev_err(&pdev->dev, "unable to map dsi registers\n");
  ret = -EINVAL;
  goto err_iomap;
}
"interrupts"是中断控制器，根据SOC自定义格式，这里是<输入类型 中断号 触发方式>，作为平台中断资源；
interrupts = <0x0 0x2c 0x104 0x0 0x2d 0x104 0x0 0x33 0x104 0x0 0x34 0x104 0x0 0x39 0x104>;
g_disp_drv.irq_no[DISP_MOD_LCD0 + i] = irq_of_parse_and_map(pdev->dev.of_node, counter);
if (!g_disp_drv.irq_no[DISP_MOD_LCD0 + i]) {
  dev_err(&pdev->dev, "irq_of_parse_and_map irq %d fail for timing controller%d\n", counter, i);
}
clocks = <0x86 0x87 0x88 0x89 0x8a 0x8b 0x8c 0x8d>;
g_disp_drv.mclk[DISP_MOD_DE] = of_clk_get(pdev->dev.of_node, counter);
if (IS_ERR(g_disp_drv.mclk[DISP_MOD_DE])) {
  dev_err(&pdev->dev, "fail to get clk for de\n");
}
