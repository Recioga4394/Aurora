#ifndef EP_CHART
#define EP_CHART

#include <TFT_eSPI.h>

class epChart
{
	public:

		class epAxis
		{
			public:
				typedef enum{
					AXIS_LEFT,
					AXIS_RIGHT,
					AXIS_BOTTOM
				}type_t;
			
			private:
				TFT_eSprite*	_canvas		= nullptr;
				type_t			_type		= AXIS_LEFT;
				bool			_reverse	= false;
				float			_x			= 0;
				float			_y			= 0;
				float			_len		= 0;
				char*			_format		= "";
				float			_min		= 0.0;
				float			_max		= 0.0;
				uint8_t			_ticksCount	= 0;
				uint8_t			_lineWidth	= 3;
				uint16_t		_size		= 0;
			public:
				epAxis(TFT_eSprite* canvas, type_t type, uint8_t lineWidth);
				void			set_area(float x, float y, float lenght)	{_x = x; _y = y; _len = lenght;};
				void			set_reverse(bool reverse)					{_reverse = reverse;};
				void			set_format(char* format)					{_format		= format;};
				void			set_min_max(float min, float max)			{_min = min;	_max = max;};
				void			set_ticks_count(uint8_t count)				{_ticksCount	= count;};
				uint16_t		get_size()									{return _size;};
				uint8_t			get_ticks_count()							{return _ticksCount;};
				float			get_pos(float value);
				float			get_tick_pos(uint8_t idx);
				void			update();
				void			draw();
		};

		typedef struct{
			int16_t		x;
			int16_t		y;
		}point_t;

		typedef struct{
			int16_t		x;
			int16_t		y;
			int16_t		w;
			int16_t		h;
		}rect_t;

	private:
		#define			BORDER_X	4
		#define			BORDER_Y	4
		TFT_eSprite*	_canvas;
		rect_t			_area;
		epAxis			_axisY1;
		epAxis			_axisY2;
		epAxis			_axisX;

		void			_draw_dashed_h_line(uint16_t x, uint16_t y, uint16_t w, uint8_t dashSize);
		void			_draw_dashed_v_line(uint16_t x, uint16_t y, uint16_t h, uint8_t dashSize);

	public:
		epChart(TFT_eSprite* canvas);
		~epChart()	{};
		void			set_area(float x, float y, float w, float h);
		void			set_axis(epAxis::type_t type, float min, float max, char* format, uint8_t ticks, bool reverse);
		void			update(float* yVal[2], float* xVal, uint16_t count);
};

#endif