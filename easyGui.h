#ifndef _XCBWIN_XCBWIN_H_
#define _XCBWIN_XCBWIN_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <xcb/xcb.h>
#include <unistd.h>
#include <inttypes.h>
//#include <png.h> //currently not used
#include <stdlib.h>
#include <stdio.h>
#include <xcb/xcb.h>

using namespace std;

class Xcbwin {
	public:
		explicit Xcbwin(bool v = false);
		~Xcbwin();

		void Open(uint16_t width, uint16_t height);
		void DrawPoint(uint16_t x, uint16_t y) const;
		void DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) const;
		void DrawRectangle( uint16_t x, uint16_t y, uint16_t width, uint16_t height) const;
		void DrawFilledRectangle( uint16_t x, uint16_t y, uint16_t width, uint16_t height) const;
		void DrawCircle( uint16_t x, uint16_t y, uint16_t width, uint16_t height) const;
		void DrawFilledCircle( uint16_t x, uint16_t y, uint16_t width, uint16_t height) const;
		void DrawText( uint16_t x, uint16_t y, const string &str ) const ;
		void DrawFunction( double (*funcPtr)(double), double minx, double maxx, double miny, double maxy ) const;
		void SetColor( double c);
		uint32_t SetColor(int r, int g, int b);
		void Red(void) { gcontextcurrent = gcontextarray[kRED];}
		void Green(void) { gcontextcurrent = gcontextarray[kGREEN];}
		void Violet(void) { gcontextcurrent = gcontextarray[kVIOLET];}
		void Blue(void) { gcontextcurrent = gcontextarray[kBLUE];}
		void Black(void) { gcontextcurrent = gcontextarray[kBLACK];}
		void Grey(void) { gcontextcurrent = gcontextarray[kGREY];}
		void LightGrey(void) { gcontextcurrent = gcontextarray[kLIGHTGREY];}
		void White(void) { gcontextcurrent = gcontextarray[kWHITE];}
		void Yellow(void) {gcontextcurrent = gcontextarray[kYELLOW];}
		void Waitev() const;
		void Close();
		void Wait()const;
		char WaitForKeypress() const;
		bool KeyIsPressed() const;
		void Flush() const;
		void Clear();
		void Screenshot();

	private:
		uint16_t width, height;
		const bool VERBOSE;
		bool closed;

		xcb_screen_t *screen;
		xcb_window_t window;
		enum ColorEnum {kRED = 0,kYELLOW,kGREEN,kBLUE,kVIOLET,kBLACK,kGREY,kLIGHTGREY,kWHITE,kSIZE};
		xcb_gcontext_t gcontext;
		xcb_gcontext_t gcontextcurrent;
		xcb_gcontext_t gcontextarray[kSIZE];
		xcb_pixmap_t pixmap;
		uint32_t last_color;

		xcb_intern_atom_cookie_t wm_protocols_cookie;
		xcb_intern_atom_cookie_t wm_delete_window_cookie;
		xcb_intern_atom_reply_t* protocols_reply;
		xcb_intern_atom_reply_t* delete_window_reply;
		xcb_colormap_t colormapId;
		xcb_connection_t *connection;

		void SetColor( uint32_t color);
		void CheckForEvent() const;
		xcb_gcontext_t GenerateContext( uint32_t color) const;

};

Xcbwin::Xcbwin(bool v) : VERBOSE(v), closed(true) {
	this->connection = xcb_connect(NULL, NULL);

	if(xcb_connection_has_error(connection)) {
		std::cout<<"\nPencere acilamadi\n";
		exit(1);
	}

	screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

	if(VERBOSE) {
		std::cout<<"\nScreen information "<<std::endl;
		std::cout<<" width: "<<screen->width_in_pixels<<std::endl;
		std::cout<<" height: "<<screen->height_in_pixels<<std::endl;
	}
}

void Xcbwin::Open(const uint16_t iwidth,const  uint16_t iheight){
  this->width = iwidth; //set variables to member-variables
  this->height = iheight;
  window = xcb_generate_id(connection);
  uint32_t mask = XCB_CW_BACK_PIXEL |XCB_CW_BORDER_PIXEL| XCB_CW_EVENT_MASK; // define basic settings for the window
  uint32_t values[4];
  values[0] = screen->white_pixel;
  values[1] = screen->white_pixel;
  values[2] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;

  xcb_create_window (connection,                             /* Connection          */
                     screen->root_depth, /* depth (same as root)*/
                     window,                           /* window Id           */
                     screen->root,                  /* parent window       */
                     0, 0,                          /* x, y                */
                     this->width, this->height,                      /* width, height       */
                     10U,                            /* border_width        */
                     XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
                     screen->root_visual,           /* visual              */
                     mask,values);                      /* use the options defined in mask and values */
  closed = false;
  // colormapId = screen->default_colormap;
  //xcb_create_colormap (connection, XCB_COLORMAP_ALLOC_NONE, colormapId, window, screen->root_visual);

  colormapId = xcb_generate_id(connection);
  xcb_create_colormap (connection, XCB_COLORMAP_ALLOC_NONE, colormapId, window, screen->root_visual);
  xcb_map_window (connection, window);
  pixmap = xcb_generate_id(connection);
  xcb_create_pixmap(connection,screen->root_depth,pixmap,window,this->width,this->height);
  gcontextarray[kRED] = GenerateContext(SetColor(65535,0,0));
  gcontextarray[kYELLOW] = GenerateContext(SetColor(65535, 65535, 0));
  gcontextarray[kBLUE] = GenerateContext(SetColor(0, 0, 65535));
  gcontextarray[kGREEN] = GenerateContext(SetColor(0, 65535, 0));
  gcontextarray[kVIOLET] = GenerateContext(SetColor(65535, 0, 65535));
  gcontextarray[kBLACK] = GenerateContext(SetColor(0, 0, 0));
  gcontextarray[kGREY] = GenerateContext(SetColor(20000, 20000, 20000));
  gcontextarray[kLIGHTGREY] = GenerateContext(SetColor(40000, 40000, 40000));
  gcontextarray[kWHITE] = GenerateContext(SetColor(65535, 65535, 65535));
  gcontext = xcb_generate_id(connection);
  mask = XCB_GC_FOREGROUND|XCB_GC_BACKGROUND| XCB_GC_LINE_WIDTH| XCB_GC_GRAPHICS_EXPOSURES;
  values[0] = screen->white_pixel;
  values[1] = screen->white_pixel;
  values[2] = 1;
  values[3] = 0;
  xcb_create_gc(connection,gcontext,pixmap,mask,values);
  White(); // set initial color to white
  DrawFilledRectangle(0,0,this->width, this->height); //set initial pixmap color to white
  Flush(); // paint the pixmap on the screen
  Black(); // set initial drawing-color to black
  wm_protocols_cookie = xcb_intern_atom(connection, 1, 12,"WM_PROTOCOLS");
  protocols_reply = xcb_intern_atom_reply(connection, wm_protocols_cookie, 0);
  wm_delete_window_cookie = xcb_intern_atom(connection, 0, 16, "WM_DELETE_WINDOW");
  delete_window_reply = xcb_intern_atom_reply(connection, wm_delete_window_cookie, 0);
}

void Xcbwin::DrawPoint(uint16_t x, uint16_t y) const {
	xcb_point_t point[1];
	point[0].x = static_cast<int16_t>(x);
	point[0].y = static_cast<int16_t>(y);

	xcb_poly_point (connection, XCB_COORD_MODE_ORIGIN, pixmap, gcontextcurrent, 1, point);
	xcb_poly_point (connection, XCB_COORD_MODE_ORIGIN, window, gcontextcurrent, 1, point);
	CheckForEvent();
}

void Xcbwin::DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) const {
	xcb_point_t point[2] ;
	point[0].x = static_cast<int16_t>(x0);
	point[0].y = static_cast<int16_t>(y0);
	point[1].x = static_cast<int16_t>(x1);
	point[1].y = static_cast<int16_t>(y1);

	xcb_poly_line (connection, XCB_COORD_MODE_ORIGIN, pixmap, gcontextcurrent, 2, point);
	xcb_poly_line (connection, XCB_COORD_MODE_ORIGIN, window, gcontextcurrent, 2, point);
	CheckForEvent();
}

void Xcbwin::DrawRectangle(uint16_t x,uint16_t y, uint16_t iwidth, uint16_t iheight) const {
	xcb_rectangle_t rectangles[] = {{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(iwidth), static_cast<uint16_t>(iheight)}};
	xcb_poly_rectangle (connection, pixmap, gcontextcurrent, 1, rectangles);
	xcb_poly_rectangle (connection, window, gcontextcurrent, 1, rectangles);
	CheckForEvent();
}

void Xcbwin::DrawFilledRectangle(uint16_t x,uint16_t y, uint16_t iwidth, uint16_t iheight) const {
	xcb_rectangle_t rectangles[] = {{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(iwidth), static_cast<uint16_t>(iheight)}};
	xcb_poly_fill_rectangle (connection, pixmap, gcontextcurrent, 1, rectangles);
	xcb_poly_fill_rectangle (connection, window, gcontextcurrent, 1, rectangles);
	CheckForEvent();
}

void Xcbwin::DrawCircle( uint16_t x, uint16_t y, uint16_t width, uint16_t height) const {
	xcb_arc_t arcs[] = {{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(width), static_cast<uint16_t>(height), 0, 360 << 6}};
	xcb_poly_arc (connection, pixmap, gcontextcurrent, 1, arcs);
	xcb_poly_arc (connection, window, gcontextcurrent, 1, arcs);
	CheckForEvent();
}

void Xcbwin::DrawFilledCircle( uint16_t x, uint16_t y, uint16_t width, uint16_t height) const {
	xcb_arc_t arcs[] = {{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(width), static_cast<uint16_t>(height), 0, 360 << 6}};
	xcb_poly_fill_arc (connection, pixmap, gcontextcurrent, 1, arcs);
	xcb_poly_fill_arc (connection, window, gcontextcurrent, 1, arcs);
	CheckForEvent();
}

void Xcbwin::DrawText( uint16_t x, uint16_t y, const std::string &str ) const {
	const char *label = str.c_str();
	xcb_image_text_8_checked(connection, static_cast<uint8_t>(strlen(label)), pixmap, gcontextcurrent, x, y, label );
	xcb_image_text_8_checked(connection, static_cast<uint8_t>(strlen(label)), window, gcontextcurrent, x, y, label );
	CheckForEvent();
}

void Xcbwin::DrawFunction( double (*funcPtr)(double), double minx, double maxx, double miny, double maxy ) const {
  // calculate the first point, and use it to store the last drawn point, for drawing lines
  double valx = minx;
  double valy = funcPtr(valx);
  uint16_t lx = 0;
  uint16_t ly = static_cast<uint16_t>((valy - maxy) * static_cast<double>(height) / (miny - maxy));
  // calculate one point for each pixel on the screen
  for (uint16_t px = 0; px < width; ++px) {
     double valx = minx + (maxx - minx) * static_cast<double>(px) / static_cast<double>(width);
     double valy = funcPtr(valx);
     // care that min and max y are swapped, since the screen coord system is up to down.
     uint16_t py = static_cast<uint16_t>((valy - maxy) * static_cast<double>(height) / (miny - maxy));
     DrawLine(lx, ly, px, py);
     lx = px;
     ly = py;
  }
}

void Xcbwin::Wait() const { //Just to be compatible to XWindow
  Waitev();
}

void Xcbwin::Waitev() const {
	Flush();
	xcb_generic_event_t *event;
	while((event = xcb_wait_for_event(connection))) {
		switch((*event).response_type & ~0x80) {
			case XCB_EXPOSE: //if expose event we copy the pixmap to the screen
        	{
          xcb_expose_event_t *ev = reinterpret_cast<xcb_expose_event_t*> (event);
          xcb_copy_area(connection,pixmap,window,gcontext,
                        static_cast<int16_t>(ev->x),
                        static_cast<int16_t>(ev->y),
                        static_cast<int16_t>(ev->x),
                        static_cast<int16_t>(ev->y),
                        static_cast<uint16_t>(ev->width),
                        static_cast<uint16_t>(ev->height));
          xcb_flush(connection);
          free(ev);
        }
        break;
	// case XCB_CLIENT_MESSAGE:
	//   if((*(xcb_client_message_event_t*)event).data.data32[0] == (*delete_window_reply).atom)
	//     {
	//       puts("Kill was pressed");
	//       exit(0);
	//       // xcb_change_property(c, XCB_PROP_MODE_REPLACE, w, (*protocols_reply).atom, 4,32,1,&(*protocols_reply).atom);
	//       return ;
	//     }
	//   exit(0);
	//   break;
      case XCB_KEY_PRESS:
        // if any key was pressed, return
        free(event);
        return;
        break;

      default:
        free(event);
        break;
    }
  }
}

char Xcbwin::WaitForKeypress() const {
	Flush();
	xcb_generic_event_t *event;
	while((event = xcb_wait_for_event(connection))) {
		switch((*event).response_type & ~0x80) {
			case XCB_EXPOSE:
			{
				xcb_expose_event_t *ev = reinterpret_cast<xcb_expose_event_t*> (event);
				xcb_copy_area(connection,pixmap,window,gcontext,
                        static_cast<int16_t>(ev->x),
                        static_cast<int16_t>(ev->y),
                        static_cast<int16_t>(ev->x),
                        static_cast<int16_t>(ev->y),
                        static_cast<uint16_t>(ev->width),
                        static_cast<uint16_t>(ev->height));
				xcb_flush(connection);
				free(ev);
			}
        	break;
	// case XCB_CLIENT_MESSAGE:
	//   if((*(xcb_client_message_event_t*)event).data.data32[0] == (*delete_window_reply).atom)
	//     {
	//       puts("Kill was pressed");
	//       exit(0);
	//       // xcb_change_property(c, XCB_PROP_MODE_REPLACE, w, (*protocols_reply).atom, 4,32,1,&(*protocols_reply).atom);
	//       return ;
	//     }
	//   exit(0);
	//   break;
			case XCB_KEY_PRESS:
			{
				xcb_key_press_event_t *bp = reinterpret_cast<xcb_key_press_event_t*> (event);
				cout << bp->detail << endl;
				free(event);
				return 0;
			}
				break;
			default:
				free(event);
				break;
		}
	}
	return 0;
}

bool Xcbwin::KeyIsPressed() const {
	xcb_generic_event_t *event = xcb_poll_for_event(connection);
	if(event) {
		if((event->response_type & ~0x80)== XCB_KEY_PRESS) {
			free(event);
			return true;
		}
	}
	free(event);
	return false;
}

void Xcbwin::Flush() const {
	xcb_flush(connection);
	xcb_copy_area(connection,pixmap,window,gcontextcurrent,0,0,0,0,this->width,this->height);
	//cout << "flushed - do not use this too often! " << endl;
}

Xcbwin::~Xcbwin() {
	xcb_free_pixmap(connection,pixmap);
	if(!closed) Xcbwin::Close();
}

void Xcbwin::Close() {
	if(connection) {
		xcb_disconnect(connection);
		closed = true;
	}
}

void Xcbwin::SetColor( uint32_t color) {
	gcontextcurrent = gcontext;

	if(color != last_color) {
		xcb_change_gc(connection, gcontext, XCB_GC_FOREGROUND, &color);
		xcb_change_gc(connection, gcontext, XCB_GC_FOREGROUND, &color);
	}
	last_color = color;
}

void Xcbwin::SetColor( double c) {
	double c1=c-floor(c);
	double c2=c1+1.0/3-floor(c1+1.0/3);
	double c3=c2+1.0/3-floor(c2+1.0/3);
	int r = 255-(c1<0.5 ? static_cast<int>(512*c1) : 511-static_cast<int>(512*c1));
	int g = 255-(c2<0.5 ? static_cast<int>(512*c2) : 511-static_cast<int>(512*c2));
	int b = 255-(c3<0.5 ? static_cast<int>(512*c3) : 511-static_cast<int>(512*c3));
	SetColor(static_cast<uint32_t>(r<<16 | g<<8 | b));
}

void Xcbwin::CheckForEvent() const {
	xcb_generic_event_t *event = xcb_poll_for_event(connection);
	if(event) {
		if((event->response_type & ~0x80)== XCB_EXPOSE){
			xcb_expose_event_t *ev = reinterpret_cast<xcb_expose_event_t*> (event);
			xcb_copy_area(connection,pixmap,window,gcontext,
                        static_cast<int16_t>(ev->x),
                        static_cast<int16_t>(ev->y),
                        static_cast<int16_t>(ev->x),
                        static_cast<int16_t>(ev->y),
                        static_cast<uint16_t>(ev->width),
                        static_cast<uint16_t>(ev->height));
          //   xcb_flush(connection);
		}
	}
	free(event);
}

uint32_t Xcbwin::SetColor(int r, int g, int b)  {
	xcb_alloc_color_reply_t *reply = xcb_alloc_color_reply (connection,xcb_alloc_color (connection,colormapId,static_cast<uint16_t>(r),static_cast<uint16_t>(g),static_cast<uint16_t>(b)),NULL ); //calculate pixel-value, that produces the requested rgb color.
	if(!reply) {
    	free(reply);
    	cout << "error - no reply" << endl;
    	cout << "given: " << r << " " << g << " " << b << endl;
    	return 0;
	}

	Xcbwin::SetColor(reply->pixel);
	uint32_t ret_color = reply->pixel;
	free(reply);
	return ret_color;
}

void Xcbwin::Clear() {
	White();
	DrawFilledRectangle(0,0,this->width, this->height);
	Flush();
	Black();
}

xcb_gcontext_t Xcbwin::GenerateContext(uint32_t color) const {
	xcb_gcontext_t tempcontext = xcb_generate_id(connection);
	uint32_t mask = XCB_GC_FOREGROUND|XCB_GC_BACKGROUND|XCB_GC_LINE_WIDTH|XCB_GC_GRAPHICS_EXPOSURES;

	uint32_t values[4];

	values[0] = color;
	values[1] = screen->white_pixel;
	values[2] = 1;
	values[3] = 0;

	xcb_create_gc(connection, tempcontext, window, mask, values);

	return tempcontext;
}

void Xcbwin::Screenshot() {
	xcb_get_image_cookie_t imgcookie = xcb_get_image(connection, XCB_IMAGE_FORMAT_Z_PIXMAP, pixmap, 0,0, width, height, static_cast<uint32_t>(-1));
	xcb_get_image_reply_t *imgreply = xcb_get_image_reply(connection, imgcookie, NULL);
	uint8_t *data = xcb_get_image_data(imgreply);

	std::ofstream file("screenshot.ppm");
	file<<"P6\n"<<width<<" "<<height<<"255\n";

	uint8_t *max = data+static_cast<uint64_t>(height)*static_cast<uint64_t>(width)*4;

	for(uint8_t *pos=data+2;pos<max;pos+=6) {
		file.write(reinterpret_cast<char*>(pos), sizeof(uint8_t));
		file.write(reinterpret_cast<char*>(--pos), sizeof(uint8_t));
		file.write(reinterpret_cast<char*>(--pos), sizeof(uint8_t));
	}

	file.close();
}

#endif // _XCBWIN_XCBWIN_H_
