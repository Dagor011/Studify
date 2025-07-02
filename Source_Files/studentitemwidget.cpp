#include "studentitemwidget.h"
//функция реализует конструктор класса StudentItemWidget, предназначенного для представления отдельного студента в графическом интерфейсе
StudentItemWidget::StudentItemWidget(QString studentName, QWidget *parent)
    : QWidget(parent)
{
    
   
    m_label = new QLabel(studentName, this);
    m_checkbox = new QCheckBox(this);
  
    QFont font;
    font.setPointSize(16);
    m_label->setFont(font);
    
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_label);
    layout->addStretch();
    layout->addWidget(m_checkbox);
   

    setLayout(layout);
   
    connect(m_checkbox, &QCheckBox::checkStateChanged, this, &StudentItemWidget::onCheckboxStateChanged);
    

}
void StudentItemWidget::onCheckboxStateChanged(int state)
{
    emit selectionChanged(state == Qt::Checked);
}
