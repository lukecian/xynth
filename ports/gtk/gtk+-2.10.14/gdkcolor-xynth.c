
#include "gdkxynth.h"

static GObjectClass *parent_class = NULL;

GdkColormap * gdk_screen_get_system_colormap (GdkScreen *screen)
{
	static GdkColormap *colormap = NULL;
	ENTER();
	if (!colormap) {
		GdkVisual *visual = gdk_visual_get_system();
		colormap = gdk_colormap_new(visual, FALSE);
	}
	LEAVE();
	return colormap;
}

GdkColormap * gdk_colormap_new (GdkVisual *visual, gboolean private_cmap)
{
	GdkColormap *colormap;
	ENTER();
	g_return_val_if_fail(visual != NULL, NULL);
	g_return_val_if_fail(visual->type == GDK_VISUAL_TRUE_COLOR, NULL);
	colormap = g_object_new(gdk_colormap_get_type(), NULL);
	colormap->visual = visual;
	colormap->size   = visual->colormap_size;
	LEAVE();
	return colormap;
}

static void gdk_colormap_init (GdkColormap *colormap)
{
	ENTER();
	colormap->size           = 0;
	colormap->colors         = NULL;
	colormap->windowing_data = NULL;
	LEAVE();
}

static void gdk_colormap_finalize (GObject *object)
{
	GdkColormap *colormap;
	ENTER();
	colormap = GDK_COLORMAP(object);
	g_free(colormap->colors);
	colormap->colors = NULL;
	G_OBJECT_CLASS(parent_class)->finalize(object);
	LEAVE();
}

static void gdk_colormap_class_init (GdkColormapClass *klass)
{
	GObjectClass *object_class;
	ENTER();
	object_class = G_OBJECT_CLASS(klass);
	parent_class = g_type_class_peek_parent(klass);
	object_class->finalize = gdk_colormap_finalize;
	LEAVE();
}

GType gdk_colormap_get_type (void)
{
	ENTER();
	static GType object_type = 0;
	if (!object_type) {
		static const GTypeInfo object_info = {
			sizeof(GdkColormapClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) gdk_colormap_class_init,
			NULL,           /* class_finalize */
			NULL,           /* class_data */
			sizeof (GdkColormap),
			0,              /* n_preallocs */
			(GInstanceInitFunc) gdk_colormap_init,
		};
		object_type = g_type_register_static(G_TYPE_OBJECT, "GdkColormap", &object_info, 0);
	}
	LEAVE();
	return object_type;
}
