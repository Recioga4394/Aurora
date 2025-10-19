#include "epChart.h"



epChart::epAxis::epAxis(TFT_eSprite* canvas, type_t type, uint8_t lineWidth)
{
	_canvas		= canvas;
	_type		= type;
	_reverse	= false;
	_lineWidth	= lineWidth;
}

float	epChart::epAxis::get_pos(float value)
{
	if (value < _min)		value	= _min;
	if (value > _max)		value	= _max;
	float	result	= (_max == _min) ? 0.5 * _len : (value - _min) * _len / (_max - _min);
	switch (_type)
	{
		case AXIS_LEFT:		return (_reverse) ? (_y + _len - result) : (_y + result);
		case AXIS_RIGHT:	return (_reverse) ? (_y + _len - result) : (_y + result);
		case AXIS_BOTTOM:	return (_reverse) ? (_x + _len - result) : (_x + result);
	}
};

float	epChart::epAxis::get_tick_pos(uint8_t idx)
{
	float	step		= (_max - _min) / _ticksCount;
	float	value		= _min + idx * step;
	return get_pos(value);
};

void	epChart::epAxis::update()
{
	char		buf[32];
	switch (_type)
	{
		case AXIS_LEFT:
		case AXIS_RIGHT:{
			snprintf(buf, sizeof(buf), _format, _min);
			uint32_t	wMin	= _canvas->textWidth(buf);
			snprintf(buf, sizeof(buf), _format, _max);
			uint32_t	wMax	= _canvas->textWidth(buf);
			_size				= (wMin > wMax) ? wMin : wMax;
			_size				+= _size / 4;
			break;}
		case AXIS_BOTTOM:
			_size				= _canvas->fontHeight();
			_size				+= _size / 4;
			break;
	}	
}

void	epChart::epAxis::draw()
{
	//Draw the axis
	switch (_type)
	{
		case AXIS_LEFT:		_canvas->drawWideLine(_x + _size, _y, _x + _size, _y + _len, _lineWidth, TFT_BLACK, TFT_BLACK);	break;
		case AXIS_RIGHT:	_canvas->drawWideLine(_x - _size, _y, _x - _size, _y + _len, _lineWidth, TFT_BLACK, TFT_BLACK);	break;
		case AXIS_BOTTOM:	_canvas->drawWideLine(_x, _y - _size, _x + _len, _y - _size, _lineWidth, TFT_BLACK, TFT_BLACK);	break;
	}

	//Draw ticks and labels
	if (_ticksCount == 0)		return;
	char			buf[32];
	const uint8_t	tickLen		= 5;
	uint8_t			count		= (_max == _min) ? 1 : _ticksCount;

	for (uint8_t idx = 0; idx <= count; idx++)
	{
		float	value	= _min + idx * (_max - _min) / _ticksCount;
		float	pos		= this->get_tick_pos(idx);
		switch (_type)
		{
			case AXIS_LEFT:
				_canvas->drawFastHLine(_x + _size, pos, tickLen, TFT_BLACK);
				snprintf(buf, sizeof(buf), _format, value);
				_canvas->setTextDatum(CR_DATUM);
				_canvas->drawString(buf, _x + _size - _size/4, pos);
				break;
			case AXIS_RIGHT:
				_canvas->drawFastHLine(_x - _size - tickLen, pos, tickLen, TFT_BLACK);
				snprintf(buf, sizeof(buf), _format, value);
				_canvas->setTextDatum(CL_DATUM);
				_canvas->drawString(buf, _x - _size, pos);
				break;
			case AXIS_BOTTOM:
				_canvas->drawFastVLine(pos, _y - _size - tickLen, tickLen, TFT_BLACK);
				snprintf(buf, sizeof(buf), _format, value);
				_canvas->setTextDatum(TC_DATUM);
				_canvas->drawString(buf, pos, _y - _size + _size/4);
				break;
		}
	}

}

//=====================================================================================================================

epChart::epChart(TFT_eSprite* canvas) :
_axisY1(canvas, epAxis::AXIS_LEFT, 2),
_axisY2(canvas, epAxis::AXIS_RIGHT, 4),
_axisX(canvas, epAxis::AXIS_BOTTOM, 2)
{
	_canvas	= canvas;
}

void	epChart::_draw_dashed_h_line(uint16_t x, uint16_t y, uint16_t w, uint8_t dashSize)
{
	uint16_t	len		= 0;
	while (len < w)
	{
		_canvas->drawFastHLine(x, y, dashSize, TFT_BLACK);
		x	+= 2 * dashSize;
		len	+= 2 * dashSize;
	}
}

void	epChart::_draw_dashed_v_line(uint16_t x, uint16_t y, uint16_t h, uint8_t dashSize)
{
	uint16_t	len		= 0;
	while (len < h)
	{
		_canvas->drawFastVLine(x, y, dashSize, TFT_BLACK);
		y	+= 2 * dashSize;
		len	+= 2 * dashSize;
	}
}

void	epChart::set_area(float x, float y, float w, float h)
{
	_area	= {x + BORDER_X, y + BORDER_Y, w - 2*BORDER_X, h - 2*BORDER_Y};
}

void	epChart::set_axis(epAxis::type_t type, float min, float max, char* format, uint8_t ticks, bool reverse)
{
	switch (type)
	{
		case epAxis::AXIS_LEFT:
			_axisY1.set_min_max(min, max);
			_axisY1.set_format(format);
			_axisY1.set_ticks_count(ticks);
			_axisY1.set_reverse(reverse);
			break;
		case epAxis::AXIS_RIGHT:
			_axisY2.set_min_max(min, max);
			_axisY2.set_format(format);
			_axisY2.set_ticks_count(ticks);
			_axisY2.set_reverse(reverse);
			break;
		case epAxis::AXIS_BOTTOM:
			_axisX.set_min_max(min, max);
			_axisX.set_format(format);
			_axisX.set_ticks_count(ticks);
			_axisX.set_reverse(reverse);
			break;
	}
}

void	epChart::update(float* yVal[2], float* xVal, uint16_t count)
{
	_axisY1.update();
	_axisY2.update();
	_axisX.update();

	_axisY1.set_area(_area.x, _area.y, _area.h - _axisX.get_size());
	_axisY2.set_area(_area.x + _area.w, _area.y, _area.h - _axisX.get_size());
	_axisX.set_area(_area.x + _axisY1.get_size(), _area.y + _area.h, _area.w - _axisY1.get_size() - _axisY2.get_size());

	_axisY1.draw();
	_axisY2.draw();
	_axisX.draw();

	uint8_t		dashSize	= 5;
	for (uint8_t idx = 0; idx <= _axisY1.get_ticks_count(); idx++)
	{
		float	pos		= _axisY1.get_tick_pos(idx);
		float	len		= _area.w - _axisY1.get_size() - _axisY2.get_size();
		_draw_dashed_h_line(_area.x + _axisY1.get_size(), pos, len, dashSize);
	}

	dashSize			= 3;
	for (uint8_t idx = 0; idx <= _axisX.get_ticks_count(); idx++)
	{
		float	pos		= _axisX.get_tick_pos(idx);
		float	len		= _area.h - _axisX.get_size();
		_draw_dashed_v_line(pos, _area.y, len, dashSize);
	}
	
	if (count == 1)
	{
		float	x		= _axisX.get_pos(xVal[0]);
		float	y[2]	= {	_axisY1.get_pos(yVal[0][0]),
							_axisY2.get_pos(yVal[1][0])	};
		_canvas->fillCircle(x, y[0], 2, TFT_BLACK);
		_canvas->fillCircle(x, y[1], 4, TFT_BLACK);
	}else
	{
		point_t		pt1[2];	//For first track
		pt1[1].x		= _axisX.get_pos(xVal[0]);
		pt1[1].y		= _axisY1.get_pos(yVal[0][0]);
		point_t		pt2[2];	//For second track
		pt2[1].x		= pt1[1].x;
		pt2[1].y		= _axisY2.get_pos(yVal[1][0]);
		
		for (uint16_t idx = 1; idx < count; idx++)
		{
			pt1[0]		= pt1[1];
			pt2[0]		= pt2[1];
			
			pt1[1].x	= _axisX.get_pos(xVal[idx]);
			pt1[1].y	= _axisY1.get_pos(yVal[0][idx]);
			pt2[1].x	= pt1[1].x;
			pt2[1].y	= _axisY2.get_pos(yVal[1][idx]);

			_canvas->drawWideLine(pt1[0].x, pt1[0].y, pt1[1].x, pt1[1].y, 2, TFT_BLACK, TFT_BLACK);
			_canvas->drawWideLine(pt2[0].x, pt2[0].y, pt2[1].x, pt2[1].y, 4, TFT_BLACK, TFT_BLACK);
		}
	}
}