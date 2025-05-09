#include "headangle.h"

HeadAngle::HeadAngle(QWidget *parent) :
    QWidget(parent)
{
    this->resize(200,200);
}
void HeadAngle::paintEvent(QPaintEvent *event)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);
    drawOuterCircle(&painter);
    drawInnerCircle(&painter);
    drawPlane(&painter);
    if(true==m_ifShowWind)
    DrawWindLine(&painter);
    drawScale(&painter);
    drawText(&painter);
    drawValue(&painter);

}
void HeadAngle::drawPlane(QPainter *painter)
{
    //默认画布大小200*200
    painter->save();
//    QPixmap pix;
//    pix.load(":/plane.png");
//    pix.scaled(QSize(180,180));
////    painter->translate(100,100); //让图片的中心作为旋转的中心
//    painter->rotate(m_currentValue); //顺时针旋转为正
////    painter->translate(-100,-100); //使原点复原

    //    painter->drawPixmap(-90,-90,180,180,pix);
    painter->rotate(m_currentValue); //顺时针旋转为正
    painter->translate(-100,-100); //由于绘制背景圆以00为圆心，绘制飞机00为原点，故做此平移
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_planeColor);
    const static QPointF planePoints[24]={
        QPointF(100,38),QPointF(105,40),QPointF(109,44),
        QPointF(111,51),QPointF(110,77),QPointF(156,106),
        QPointF(156,125),QPointF(110,103),QPointF(107,140),
        QPointF(126,150),QPointF(128,159),QPointF(106,155),
        QPointF(94,155),QPointF(72,159),QPointF(74,150),
        QPointF(93,140),QPointF(90,103),QPointF(44,125),
        QPointF(44,106),QPointF(90,77),QPointF(89,51),
        QPointF(91,44),QPointF(95,40),QPointF(100,38)
    };
    painter->drawPolygon(planePoints, 24);
    painter->restore();
}

void HeadAngle::DrawWindLine(QPainter *_painter)
{
    // 初始化
    _painter->save();
//    _painter->resetTransform(); // 重设画笔
//    _painter->translate(QPoint(300,300));
    _painter->setPen(QPen(m_windColor, 3));

    // 绘制线段
    double _len=60;
    QLine _line(QPoint(0,-_len), QPoint(0,_len-10));
    _painter->rotate(m_windAngle);
    _painter->drawLine(_line);


    // 绘制箭头
    int off_x = 10;
    QPainterPath _path;
    _path.moveTo( -5,-(_len-off_x));
    _path.lineTo(0,-_len);
    _path.lineTo(5,-(_len-off_x));
    _painter->drawPath(_path);
    //绘制箭尾
    QPainterPath pathTail;
    pathTail.moveTo( -5,_len);
    pathTail.lineTo(0,_len-10);
    pathTail.lineTo(5,_len);
    _painter->drawPath(pathTail);

    //绘制风向显示文字背景
    _painter->setBrush(m_windColor);
    double radius=qMax(m_rectWidthAndHeight.width(),m_rectWidthAndHeight.height());
    _painter->drawEllipse(-radius/2,-radius/2,radius,radius);
    //绘制风向文字
    _painter->save();
    _painter->setPen(m_textColor);
    _painter->setFont(m_font);
    int length=90;
    QString windAngleStr = QString("%1").arg((double)m_windAngle, 0, 'f', m_precision);
    QRectF windRect(-length/2, -length/2, length, length);
    _painter->drawText(windRect,Qt::AlignCenter,windAngleStr);
    _painter->restore();
    _painter->restore();
}

void HeadAngle::drawOuterCircle(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_outerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}
void HeadAngle::drawInnerCircle(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_innerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}
void HeadAngle::drawScale(QPainter *painter)
{
    int radius = 72;
    painter->save();

//    painter->rotate(startAngle);
    int scaleMajor=4;
    int scaleMinor=3;
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (360.0 ) / steps;

    QPen pen;
    pen.setColor(m_scaleColor);
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 10, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}
void HeadAngle::drawValue(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(m_textColor);

    painter->setFont(m_font);

    QString strValue = QString("%1").arg((double)m_currentValue, 0, 'f', m_precision);

    QRectF textRect(-m_rectWidthAndHeight.width()/2, radius-m_rectWidthAndHeight.height()-3, m_rectWidthAndHeight.width(), m_rectWidthAndHeight.height());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_planeColor);
    painter->drawRect(textRect);
    painter->restore();
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void HeadAngle::drawText(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(m_scaleColor);


    painter->setFont(m_font);
    double textHeight = fontMetrics().height();

    QRectF textRect(-radius, -radius+7, radius * 2, radius * 2);
    QString strValue =QStringLiteral("北");
    painter->drawText(textRect, Qt::AlignHCenter, strValue);

    painter->restore();
}

QColor HeadAngle::getScaleColor() const
{
    return  m_scaleColor;
}

void HeadAngle::setPlaneAngle(double value)
{
    m_currentValue=value;
    update();
}
void HeadAngle::setPlaneAngle(int value)
{
    m_currentValue=(double)value;
    update();
}

void HeadAngle::setWindAngle(double value)
{
    m_windAngle=value;
    update();
}

void HeadAngle::setWindAngle(int value)
{
    m_windAngle=(double)value;
    update();
}
void HeadAngle::setScaleColor(QColor color)
{
    m_scaleColor=color;
    update();
}
QColor HeadAngle::getOuterCircleColor() const
{
    return m_outerCircleColor;
}
void HeadAngle::setOuterCircleColor(QColor color)
{
    m_outerCircleColor=color;
    update();
}
QColor HeadAngle::getInnerCircleColor() const
{
    return m_innerCircleColor;
}
void HeadAngle::setInnerCircleColor(QColor color)
{
    m_innerCircleColor=color;
    update();
}
QColor HeadAngle::getTextColor() const
{
    return m_textColor;
}
void HeadAngle::setTextColor(QColor color)
{
    m_textColor=color;
    update();
}
QColor HeadAngle::getTextRectColor() const
{
    return m_textRectColor;
}
void HeadAngle::setTextRectColor(QColor color)
{
    m_textRectColor=color;
    update();
}
QColor HeadAngle::getPlaneColor() const
{
    return m_planeColor;
}

uint HeadAngle::getPrecison() const
{
    return  m_precision;
}

QFont HeadAngle::getFont() const
{
    return  m_font;
}

QSizeF HeadAngle::getRect() const
{
    return  m_rectWidthAndHeight;
}

QColor HeadAngle::getWindColor() const
{
    return  m_windColor;
}

bool HeadAngle::getShow() const
{
    return  m_ifShowWind;
}
void HeadAngle::setPlaneColor(QColor color)
{
    m_planeColor=color;
    update();
}

void HeadAngle::setPrecison(uint precision)
{
    if(precision>5)
        return;
    m_precision=precision;
    update();
}

void HeadAngle::setFont(QFont font)
{
    m_font=font;
//    this->setFont(font);
    update();
}

void HeadAngle::setRect(QSizeF widthAndHeight)
{
    m_rectWidthAndHeight=widthAndHeight;
    update();
}

void HeadAngle::setWindColor(QColor color)
{
    m_windColor=color;
    update();
}

void HeadAngle::setShow(bool checked)
{
    m_ifShowWind=checked;
    update();
}
