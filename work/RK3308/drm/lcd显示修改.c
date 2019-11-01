1. kernel\drivers\gpu\drm\rockchip\rockchip_vop_reg.c

static const struct vop_win_data rk3366_vop_lit_win_data[] = {

		{ .base = 0x00, .phy = &rk3366_lit_win1_data,
	  .type = DRM_PLANE_TYPE_PRIMARY },

	  	{ .base = 0x00, .phy = &rk3366_lit_win0_data,
	  .type = DRM_PLANE_TYPE_CURSOR },
};

kernel\drivers\gpu\drm\rockchip\rockchip_drm_vop.c
static int vop_crtc_atomic_check(struct drm_crtc *crtc,
				 struct drm_crtc_state *crtc_state)
{
	sort(pzpos, cnt, sizeof(pzpos[0]), vop_zpos_cmp, NULL);

	for (i = 0, cnt = 0; i < vop_data->win_size; i++) {
		const struct vop_win_data *win_data = &vop_data->win[i];
		int shift = i * 2;

		if (win_data->phy) {
			struct vop_zpos *zpos = &pzpos[cnt++];

			dsp_layer_sel |= zpos->win_id << shift;
		} else {
			dsp_layer_sel |= i << shift;
		}
	}

	/* add by steven;由于RK的算法的出的dsp_layer_sel为4; 但是我们需要将win1设置为primary,故这里将dsp_layer_sel设置为1，
	 * win0在win1的上面;
	*/
	dsp_layer_sel = 1;

	s->dsp_layer_sel = dsp_layer_sel;

	vop_dclk_source_generate(crtc, crtc_state);

err_free_pzpos:
	kfree(pzpos);
	return ret;
}

2. 背光修改
	 Symbol: BACKLIGHT_PWM [=n]                                                                                                                                                     |
  | Type  : tristate                                                                                                                                                               |
  | Prompt: Generic PWM based Backlight Driver                                                                                                                                     |
  |   Location:                                                                                                                                                                    |
  |     -> Device Drivers                                                                                                                                                          |
  |       -> Graphics support                                                                                                                                                      |
  |         -> Backlight & LCD device support (BACKLIGHT_LCD_SUPPORT [=y])                                                                                                         |
  | (2)       -> Lowlevel Backlight controls (BACKLIGHT_CLASS_DEVICE [=y])                                                                                                         |
  |   Defined at drivers/video/backlight/Kconfig:261                                                                                                                               |
  |   Depends on: HAS_IOMEM [=y] && BACKLIGHT_LCD_SUPPORT [=y] && BACKLIGHT_CLASS_DEVICE [=y] && PWM [=y]

	/sys/class/backlight/backlight/brightness

3. 开机显示修改
1) drivers/video/drm/bmp_helper.c
	case 24:
		if (get_unaligned_le32(&bmp->header.compression)) {
			printf("can't not support compression for 24bit bmap");
			return -1;
		}
		printf("..............flip:%d;\n",flip);

		printf("..............flip:%d;\n",flip);
		stride = ALIGN(width * 3, 4);
		if (flip)
			src += stride * (height - 1);

		for (i = 0; i < height; i++) {

			if(flip)
			{
				int j;
				for(j = 0; j < width; j++)
				{
					dst[j*3 + 2] = src[j*3];
					dst[j*3 + 1] = src[j*3 + 1];
					dst[j*3] 	 = src[j*3 + 2];
				}

			}else
			{
				memcpy(dst, src, 3 * width);
			}
			dst += stride;
			src += stride;
			if (flip)
				src -= stride * 2;
		}
		break;
2) drivers/video/drm/rockchip_display.c
static bool can_direct_logo(int bpp)
{
/*	return bpp == 24 || bpp == 32; */
	return bpp == 32;

}
3) drivers/video/drm/rockchip_vop.c
rockchip_vop_init
	switch (conn_state->bus_format) {
	case MEDIA_BUS_FMT_RGB565_1X16:
		val = DITHER_DOWN_EN(1) | DITHER_DOWN_MODE(RGB888_TO_RGB565);
		conn_state->output_mode = ROCKCHIP_OUT_MODE_P565;
		break;
	case MEDIA_BUS_FMT_RGB666_1X18:
	case MEDIA_BUS_FMT_RGB666_1X24_CPADHI:
		val = DITHER_DOWN_EN(1) | DITHER_DOWN_MODE(RGB888_TO_RGB666);
		break;
4) drivers/video/drm/rockchip_vop_reg.c
win0改为win1
const struct vop_data rk3308_vop = {
	.version = VOP_VERSION(2, 7),
	.max_output = {1920, 1080},
	.ctrl = &rk3308_ctrl_data,
	.win = &rk3366_win1_data,
	.line_flag = &rk3366_vop_lite_line_flag,
	.reg_len = RK3366_LIT_FRC_LOWER01_0 * 4,
};

4. 显示开机画面前，会显示一下白屏
drivers/video/drm/rockchip_panel.c
static int rockchip_panel_enable(struct display_state *state)
{
	struct panel_state *panel_state = &state->panel_state;
	struct rockchip_panel_plat *plat = dev_get_platdata(panel_state->dev);
	struct rockchip_panel_priv *priv = dev_get_priv(panel_state->dev);

	if (priv->enabled)
		return 0;

	mdelay(plat->delay.enable);

	/*	///在打开背光之前需要添加一些延时，否则会先白屏一下，然后再显示开机图片 */
	mdelay(150);
	if (priv->backlight)
		backlight_enable(priv->backlight);

	priv->enabled = true;

	return 0;
}

5. 对比度的调节
内核中：drivers/gpu/drm/rockchip/rockchip_rgb.c
static int
rockchip_rgb_encoder_atomic_check(struct drm_encoder *encoder,
				   struct drm_crtc_state *crtc_state,
				   struct drm_connector_state *conn_state)

	s->output_type = DRM_MODE_CONNECTOR_LVDS;
//	s->output_type = DRM_MODE_CONNECTOR_DPI;
	s->tv_state = &conn_state->tv;
	s->eotf = TRADITIONAL_GAMMA_SDR;
	s->color_space = V4L2_COLORSPACE_DEFAULT;



ln -s /bin/dsp /tmp/dsp
ln -s /basic/voice_dsp.ini /tmp/voice_dsp.ini
/tmp/dsp /tmp 20 2 0 &
