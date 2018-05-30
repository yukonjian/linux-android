在fb.h中包含了framebuffer的主要结构体
1. struct fb_var_screeninfo   /* 描述了显示卡的特性 */

struct fb_var_screeninfo
{
__u32 xres; /* visible resolution */
__u32 yres;
__u32 xres_virtual; /* virtual resolution */
__u32 yres_virtual;
__u32 xoffset; /* offset from virtual to visible resolution */
__u32 yoffset;
__u32 bits_per_pixel; /* guess what */
__u32 grayscale; /* != 0 Gray levels instead of colors */
struct fb_bitfield red; /* bitfield in fb mem if true color, */
struct fb_bitfield green; /* else only length is significant */
struct fb_bitfield blue;
struct fb_bitfield transp; /* transparency */
__u32 nonstd; /* != 0 Non standard pixel format */
__u32 activate; /* see FB_ACTIVATE_* */
__u32 height; /* height of picture in mm */
__u32 width; /* width of picture in mm */
__u32 accel_flags; /* acceleration flags (hints) */
/* Timing: All values in pixclocks, except pixclock (of course) */
__u32 pixclock; /* pixel clock in ps (pico seconds) */
__u32 left_margin; /* time from sync to picture */
__u32 right_margin; /* time from picture to sync */
__u32 upper_margin; /* time from sync to picture */
__u32 lower_margin;
__u32 hsync_len; /* length of horizontal sync */
__u32 vsync_len; /* length of vertical sync */
__u32 sync; /* see FB_SYNC_* */
__u32 vmode; /* see FB_VMODE_* */
__u32 reserved[6]; /* Reserved for future compatibility */
};

2. fb_fix_screeninfon   /* 显示卡的属性，并且系统运行时不能被修改 */

struct fb_fix_screeninfo {
char id[16]; /* identification string eg "TT Builtin" */
unsigned long smem_start; /* Start of frame buffer mem */
/* (physical address) */
__u32 smem_len; /* Length of frame buffer mem */
__u32 type; /* see FB_TYPE_* */
__u32 type_aux; /* Interleave for interleaved Planes */
__u32 visual; /* see FB_VISUAL_* */
__u16 xpanstep; /* zero if no hardware panning */
__u16 ypanstep; /* zero if no hardware panning */
__u16 ywrapstep; /* zero if no hardware ywrap */
__u32 line_length; /* length of a line in bytes */
unsigned long mmio_start; /* Start of Memory Mapped I/O */
/* (physical address) */
__u32 mmio_len; /* Length of Memory Mapped I/O */
__u32 accel; /* Type of acceleration available */
__u16 reserved[3]; /* Reserved for future compatibility */
};

3. struct fb_cmap   /* 描述设备无关的颜色映射信息。可以通过FBIOGETCMAP 和 FBIOPUTCMAP 对应的ioctl操作设定或获取颜色映射信息. */

struct fb_cmap {
__u32 start; /* First entry */
__u32 len; /* Number of entries */
__u16 *red; /* Red values */
__u16 *green;
__u16 *blue;
__u16 *transp; /* transparency, can be NULL */
};

4. struct fb_info   /* 定义当显卡的当前状态；fb_info结构仅在内核中可见，在这个结构中有一个fb_ops指针， 指向驱动设备工作所需的函数集。  */

struct fb_info {
char modename[40]; /* default video mode */
kdev_t node;
int flags;
int open; /* Has this been open already ? */
#define FBINFO_FLAG_MODULE 1 /* Low-level driver is a module */
struct fb_var_screeninfo var; /* Current var */
struct fb_fix_screeninfo fix; /* Current fix */
struct fb_monspecs monspecs; /* Current Monitor specs */
struct fb_cmap cmap; /* Current cmap */
struct fb_ops *fbops;
char *screen_base; /* Virtual address */
struct display *disp; /* initial display variable */
struct vc_data *display_fg; /* Console visible on this display */
char fontname[40]; /* default font name */
devfs_handle_t devfs_handle; /* Devfs handle for new name */
devfs_handle_t devfs_lhandle; /* Devfs handle for compat. symlink */
int (*changevar)(int); /* tell console var has changed */
int (*switch_con)(int, struct fb_info*);
/* tell fb to switch consoles */
int (*updatevar)(int, struct fb_info*);
/* tell fb to update the vars */
void (*blank)(int, struct fb_info*); /* tell fb to (un)blank the screen */
/* arg = 0: unblank */
/* arg > 0: VESA level (arg-1) */
void *pseudo_palette; /* Fake palette of 16 colors and
the cursor's color for non
palette mode */
/* From here on everything is device dependent */
void *par;
};

5. struct fb_ops    /* 用户应用可以使用ioctl()系统调用来操作设备，这个结构就是用一支持ioctl()的这些操作的。 */

struct fb_ops {
/* open/release and usage marking */
struct module *owner;
int (*fb_open)(struct fb_info *info, int user);
int (*fb_release)(struct fb_info *info, int user);
/* get non settable parameters */
int (*fb_get_fix)(struct fb_fix_screeninfo *fix, int con,
struct fb_info *info);
/* get settable parameters */
int (*fb_get_var)(struct fb_var_screeninfo *var, int con,
struct fb_info *info);
/* set settable parameters */
int (*fb_set_var)(struct fb_var_screeninfo *var, int con,
struct fb_info *info);
/* get colormap */ 
int (*fb_get_cmap)(struct fb_cmap *cmap, int kspc, int con,
struct fb_info *info);
/* set colormap */
int (*fb_set_cmap)(struct fb_cmap *cmap, int kspc, int con,
struct fb_info *info);
/* pan display (optional) */
int (*fb_pan_display)(struct fb_var_screeninfo *var, int con,
struct fb_info *info);
/* perform fb specific ioctl (optional) */
int (*fb_ioctl)(struct inode *inode, struct file *file, unsigned int cmd,
unsigned long arg, int con, struct fb_info *info);
/* perform fb specific mmap */
int (*fb_mmap)(struct fb_info *info, struct file *file, struct
vm_area_struct *vma);
/* switch to/from raster image mode */
int (*fb_rasterimg)(struct fb_info *info, int start);
};
