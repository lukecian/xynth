
#include "gdk-xynth.h"

static gpointer parent_class = NULL;

static void gdk_xynth_draw_rectangle (GdkDrawable *drawable, GdkGC *gc, gboolean filled, gint x, gint y, gint width, gint height)
{
	GdkColor color;
	GdkDrawableImplXynth *draw_impl;
	ENT();
	draw_impl = GDK_DRAWABLE_IMPL_XYNTH(drawable);
	if (GDK_GC_XYNTH(gc)->values_mask & GDK_GC_FOREGROUND) {
		color = GDK_GC_XYNTH(gc)->values.foreground;
	} else if (GDK_IS_WINDOW(draw_impl->wrapper)) {
		color = ((GdkWindowObject *) (draw_impl->wrapper))->bg_color;
	} else {
		color.pixel = 0;
	}
	DBG("filled:%d, x:%d, y:%d, w:%d, h:%d c:%d(%d, %d, %d)", filled, x, y, width, height, color.pixel, color.red, color.green, color.blue);
	if (filled) {
		s_fillbox(draw_impl->object->surface, x, y, width, height, color.pixel);
		DBG("OBJ: %p buf:%d %d %d %d win:%d %d %d %d", draw_impl->object,
		draw_impl->object->surface->buf->x,draw_impl->object->surface->buf->y,draw_impl->object->surface->buf->w,draw_impl->object->surface->buf->h,
		draw_impl->object->surface->win->x,draw_impl->object->surface->win->y,draw_impl->object->surface->win->w,draw_impl->object->surface->win->h);
		w_object_update(draw_impl->object, draw_impl->object->surface->win);
	} else {
		NIY();
	}
	LEV();
}

static void gdk_xynth_draw_arc (GdkDrawable *drawable, GdkGC *gc, gboolean filled, gint x, gint y, gint width, gint height, gint angle1, gint angle2)
{
	NIY();
}

static void gdk_xynth_draw_polygon (GdkDrawable *drawable, GdkGC *gc, gboolean filled, GdkPoint *points, gint npoints)
{
	NIY();
}

static void gdk_xynth_draw_text (GdkDrawable *drawable, GdkFont *font, GdkGC *gc, gint x, gint y, const gchar *text, gint text_length)
{
	NIY();
}

static void gdk_xynth_draw_text_wc (GdkDrawable *drawable, GdkFont *font, GdkGC *gc, gint x, gint y, const GdkWChar *text, gint text_length)
{
	NIY();
}

static void gdk_xynth_draw_glyphs (GdkDrawable *drawable, GdkGC *gc, PangoFont *font, gint x, gint y, PangoGlyphString *glyphs)
{
	NIY();
}

static void gdk_xynth_draw_drawable (GdkDrawable *drawable, GdkGC *gc, GdkPixmap *src, gint xsrc, gint ysrc, gint xdest, gint ydest, gint width, gint height)
{
	NIY();
}

static void gdk_xynth_draw_image (GdkDrawable *drawable, GdkGC *gc, GdkImage *image, gint xsrc, gint ysrc, gint xdest, gint ydest, gint width, gint height)
{
	NIY();
}

static void gdk_xynth_draw_points (GdkDrawable *drawable, GdkGC *gc, GdkPoint *points, gint npoints)
{
	NIY();
}

static void gdk_xynth_draw_segments (GdkDrawable *drawable, GdkGC *gc, GdkSegment *segs, gint nsegs)
{
	NIY();
}

static void gdk_xynth_draw_lines (GdkDrawable *drawable, GdkGC *gc, GdkPoint *points, gint npoints)
{
	NIY();
}

static GdkColormap * gdk_xynth_get_colormap (GdkDrawable *drawable)
{
	GdkColormap *retval;
	GdkDrawableImplXynth *draw_impl;
	ENT();
	draw_impl = GDK_DRAWABLE_IMPL_XYNTH(drawable);
	retval = draw_impl->colormap;
	if (!retval) {
		retval = gdk_colormap_get_system();
	}
	LEV();
	return retval;
}

static void gdk_xynth_set_colormap (GdkDrawable *drawable, GdkColormap *colormap)
{
	GdkDrawableImplXynth *impl;
	ENT();
	impl = GDK_DRAWABLE_IMPL_XYNTH(drawable);
	if (impl->colormap == colormap) {
		return;
	}
	if (impl->colormap) {
		g_object_unref(impl->colormap);
	}
	impl->colormap = colormap;
	if (impl->colormap) {
		g_object_ref(impl->colormap);
	}
	LEV();
}

static gint gdk_xynth_get_depth (GdkDrawable *drawable)
{
	ENT();
	LEV();
	return gdk_drawable_get_depth(GDK_DRAWABLE_IMPL_XYNTH(drawable)->wrapper);
}

static GdkScreen * gdk_xynth_get_screen (GdkDrawable *drawable)
{
	ENT();
	LEV();
	return gdk_screen_get_default();
}

static GdkVisual * gdk_xynth_get_visual (GdkDrawable *drawable)
{
	NIY();
}

static void gdk_xynth_get_size (GdkDrawable *drawable, gint *width, gint *height)
{
	ENT();
	g_return_if_fail(GDK_IS_WINDOW_IMPL_XYNTH(drawable));
	if (width) {
		*width = GDK_WINDOW_IMPL_XYNTH(drawable)->width;
	}
	if (height) {
		*height = GDK_WINDOW_IMPL_XYNTH(drawable)->height;
	}
	LEV();
}

static GdkImage * gdk_xynth_copy_to_image (GdkDrawable *drawable, GdkImage *image, gint src_x, gint src_y, gint dest_x, gint dest_y, gint width, gint height)
{
	NIY();
}

static void gdk_xynth_drawable_finalize (GObject *object)
{
	ENT();
	gdk_drawable_set_colormap(GDK_DRAWABLE(object), NULL);
	G_OBJECT_CLASS (parent_class)->finalize (object);
	LEV();
}

static void gdk_drawable_impl_xynth_class_init (GdkDrawableImplXynthClass *klass)
{
	GdkDrawableClass *drawable_class = GDK_DRAWABLE_CLASS(klass);
	GObjectClass *object_class = G_OBJECT_CLASS(klass);
	ENT();
	parent_class = g_type_class_peek_parent(klass);
	object_class->finalize = gdk_xynth_drawable_finalize;
	drawable_class->create_gc = gdk_xynth_gc_new;
	drawable_class->draw_rectangle = gdk_xynth_draw_rectangle;
	drawable_class->draw_arc = gdk_xynth_draw_arc;
	drawable_class->draw_polygon = gdk_xynth_draw_polygon;
	drawable_class->draw_text = gdk_xynth_draw_text;
	drawable_class->draw_text_wc = gdk_xynth_draw_text_wc;
	drawable_class->draw_drawable = gdk_xynth_draw_drawable;
	drawable_class->draw_points = gdk_xynth_draw_points;
	drawable_class->draw_segments = gdk_xynth_draw_segments;
	drawable_class->draw_lines = gdk_xynth_draw_lines;
	drawable_class->draw_glyphs = gdk_xynth_draw_glyphs;
	drawable_class->draw_image = gdk_xynth_draw_image;
	drawable_class->set_colormap = gdk_xynth_set_colormap;
	drawable_class->get_colormap = gdk_xynth_get_colormap;
	drawable_class->get_size = gdk_xynth_get_size;
	drawable_class->get_depth = gdk_xynth_get_depth;
	drawable_class->get_screen = gdk_xynth_get_screen;
	drawable_class->get_visual = gdk_xynth_get_visual;
	drawable_class->_copy_to_image = gdk_xynth_copy_to_image;
	LEV();
}

GType _gdk_drawable_impl_xynth_get_type (void)
{
	static GType object_type = 0;
	ENT();
	if (!object_type) {
		static const GTypeInfo object_info = {
			sizeof(GdkDrawableImplXynthClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gdk_drawable_impl_xynth_class_init,
			NULL,           /* class_finalize */
			NULL,           /* class_data */
			sizeof(GdkDrawableImplXynth),
			0,              /* n_preallocs */
			(GInstanceInitFunc) NULL,
		};
		object_type = g_type_register_static(GDK_TYPE_DRAWABLE, "GdkDrawableImplXynth", &object_info, 0);
	}
	LEV();
	return object_type;
}
