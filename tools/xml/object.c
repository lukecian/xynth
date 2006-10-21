
#include "object_xml.h"

static int area_hide = 0;

void frame_red_draw (w_object_t *object)
{
	s_fillbox(object->surface, 0, 0, object->surface->width, object->surface->height, s_rgbcolor(object->surface, 255, 0, 0));
}

void frame_green_draw (w_object_t *object)
{
	s_fillbox(object->surface, 0, 0, object->surface->width, object->surface->height, s_rgbcolor(object->surface, 0, 255, 0));
}

void frame_blue_draw (w_object_t *object)
{
	s_fillbox(object->surface, 0, 0, object->surface->width, object->surface->height, s_rgbcolor(object->surface, 0, 0, 255));
}

void frame_white_draw (w_object_t *object)
{
	s_fillbox(object->surface, 0, 0, object->surface->width, object->surface->height, s_rgbcolor(object->surface, 255, 255, 255));
}

void button_hide_draw (w_object_t *object)
{
	if (area_hide) {
		w_textbox_set_str(textbox_hide->object, "show area");
	} else {
		w_textbox_set_str(textbox_hide->object, "hide area");
	}
}

void button_hide_pressed (w_object_t *object, int button)
{
	area_hide++;
	area_hide = (area_hide) % 2;
	if (area_hide) {
		w_object_hide(area->object);
	} else {
		w_object_show(area->object);
	}
}

void button_blender_pressed (w_object_t *object, int button)
{
	w_object_move(frame_red->object, (rand() + 1) % area->object->surface->buf->w, (rand() + 1) % area->object->surface->buf->h,
	                                 (rand() + 1) % area->object->surface->buf->w, (rand() + 1) % area->object->surface->buf->h);
	w_object_move(frame_green->object, (rand() + 1) % area->object->surface->buf->w, (rand() + 1) % area->object->surface->buf->h,
	                                   (rand() + 1) % area->object->surface->buf->w, (rand() + 1) % area->object->surface->buf->h);
	w_object_move(frame_blue->object, (rand() + 1) % area->object->surface->buf->w, (rand() + 1) % area->object->surface->buf->h,
	                                  (rand() + 1) % area->object->surface->buf->w, (rand() + 1) % area->object->surface->buf->h);
	w_object_move(frame_white->object, (rand() + 1) % area->object->surface->buf->w, (rand() + 1) % area->object->surface->buf->h,
	                                   (rand() + 1) % area->object->surface->buf->w, (rand() + 1) % area->object->surface->buf->h);
}

void button_focus_pressed (w_object_t *object, int button)
{
	int r;
	w_frame_t *obj[] = {
		frame_red,
		frame_green,
		frame_blue,
		frame_white
	};
	r = rand() % 4;
	w_object_show(obj[r]->object);
}