#include "pdfgenerator.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFontMetrics>
#include <QRectF>
#include <QFontDatabase>
#include <iostream>

// Инициализация объекта генератора PDF
PdfGenerator::PdfGenerator(QObject *parent) :
    QObject(parent)
{}

void PdfGenerator::generatePdf(const QString &filename, const std::vector<Student> &students)
{
    QPdfWriter writer(filename);
    writer.setPageSize(QPageSize::A4);                            // Формат А4
    writer.setResolution(72);                                     // Разрешение 72 dpi

    QPainter painter(&writer);
    painter.setPen(Qt::black);

    double pageWidth = writer.width();                             // Ширина страницы в пикселях
    double pageHeight = writer.height();                           // Высота страницы в пикселях

    // Шрифты и метрики шрифтов
    QFont smallHeadings("Times New Roman", 6);
    QFont boldHeadings("Times New Roman", 6, QFont::Bold);
    QFontMetrics smallHeadingsMetrics(smallHeadings);
    QFontMetrics boldHeadingsMetrics(boldHeadings);

    QFont smallBodyFont("Times New Roman", 6);
    QFont boldBodyFont("Times New Roman", 6, QFont::Bold);
    QFontMetrics smallBodyFontMetrics(smallBodyFont);
    QFontMetrics boldBodyFontMetrics(boldBodyFont);

    QFont smallInfoFont("Times New Roman", 4);
    QFontMetrics smallInfoFontMetrics(smallInfoFont);

    int yPosition = -5;

    constexpr int spaceNeeded = 250;
    constexpr int bottomMargin = 50;
    double halfPageWidth = pageWidth / 2;

    for (const Student &student : students) {
        if (yPosition + spaceNeeded > pageHeight - bottomMargin) {
            writer.newPage();
            yPosition = 150;
        }

        // Заголовочная информация
        QString topLine = "АВТОНОМНАЯ НЕКОММЕРЧЕСКАЯ ОРГАНИЗАЦИЯ";
        QString middleLine = "ПРОФЕССИОНАЛЬНАЯ ОБРАЗОВАТЕЛЬНАЯ ОРГАНИЗАЦИЯ";
        QString bottomLine = "МОСКОВСКИЙ МЕЖДУНАРОДНЫЙ КОЛЛЕДЖ ЦИФРОВЫХ ТЕХНОЛОГИЙ \"АКАДЕМИЯ ТОП\"";

        QRectF topTitleRect(-5, yPosition, halfPageWidth, smallHeadingsMetrics.height());
        QRectF middleTitleRect(-5, yPosition += 7, halfPageWidth, smallHeadingsMetrics.height());
        QRectF bottomTitleRect(-5, yPosition += 7, halfPageWidth, boldHeadingsMetrics.height());

        painter.setFont(smallHeadings);
        painter.drawText(topTitleRect, Qt::AlignHCenter | Qt::AlignTop, topLine);
        painter.drawText(middleTitleRect, Qt::AlignHCenter | Qt::AlignTop, middleLine);

        painter.setFont(boldHeadings);
        painter.drawText(bottomTitleRect, Qt::AlignHCenter | Qt::AlignTop, bottomLine);

        yPosition += 20;

        // Поле с информацией о студенте
        qreal textStartX = 100;
        QRectF contentRect(textStartX, yPosition, halfPageWidth, boldHeadingsMetrics.height());

        // Устанавливаем шрифт для основного текста
        painter.setFont(boldBodyFont);
        painter.drawText(contentRect.topLeft(), "Студентский билет №");              // Название поля
        painter.drawLine(contentRect.topLeft().x(), contentRect.topLeft().y() + smallBodyFontMetrics.ascent(),
                         contentRect.topLeft().x() + halfPageWidth / 2.2, contentRect.topLeft().y() + smallBodyFontMetrics.ascent());  // Линия под номером билета

        contentRect.setHeight(smallBodyFontMetrics.height());
        painter.setFont(smallBodyFont);
        painter.drawText(contentRect.topLeft() + QPointF(60, 0), student.getTicketNumber()); // Значение поля

        // Остальная информация о студенте
        painter.drawText(contentRect.topLeft() + QPointF(0, 15), "Фамилия ");           // Название поля
        painter.drawLine(contentRect.topLeft().x(), contentRect.topLeft().y() + 15 + smallBodyFontMetrics.ascent(),
                         contentRect.topLeft().x() + halfPageWidth / 2.2, contentRect.topLeft().y() + 15 + smallBodyFontMetrics.ascent()); // Линия под фамилией
        painter.drawText(contentRect.topLeft() + QPointF(60, 15), student.getLastName());  // Значение поля

        painter.drawText(contentRect.topLeft() + QPointF(0, 30), "Имя ");               // Название поля
        painter.drawLine(contentRect.topLeft().x(), contentRect.topLeft().y() + 30 + smallBodyFontMetrics.ascent(),
                         contentRect.topLeft().x() + halfPageWidth / 2.2, contentRect.topLeft().y() + 30 + smallBodyFontMetrics.ascent()); // Линия под именем
        painter.drawText(contentRect.topLeft() + QPointF(60, 30), student.getFirstName());  // Значение поля

        painter.drawText(contentRect.topLeft() + QPointF(0, 45), "Отчество ");          // Название поля
        painter.drawLine(contentRect.topLeft().x(), contentRect.topLeft().y() + 45 + smallBodyFontMetrics.ascent(),
                         contentRect.topLeft().x() + halfPageWidth / 2.2, contentRect.topLeft().y() + 45 + smallBodyFontMetrics.ascent()); // Линия под отчеством
        painter.drawText(contentRect.topLeft() + QPointF(60, 45), student.getMiddleName());  // Значение поля

        painter.drawText(contentRect.topLeft() + QPointF(0, 60), QString("Форма обучения ")); // Название поля
        painter.drawLine(contentRect.topLeft().x(), contentRect.topLeft().y() + 60 + smallBodyFontMetrics.ascent(),
                         contentRect.topLeft().x() + halfPageWidth / 2.2, contentRect.topLeft().y() + 60 + smallBodyFontMetrics.ascent()); // Линия под формой обучения
        painter.drawText(contentRect.topLeft() + QPointF(60, 60), student.getFormOfStudy());  // Значение поля

        painter.drawText(contentRect.topLeft() + QPointF(0, 75), "Зачислен приказом ");     // Название поля
        painter.drawLine(contentRect.topLeft().x(), contentRect.topLeft().y() + 75 + smallBodyFontMetrics.ascent(),
                         contentRect.topLeft().x() + halfPageWidth / 2.2, contentRect.topLeft().y() + 75 + smallBodyFontMetrics.ascent()); // Линия под приказом
        painter.drawText(contentRect.topLeft() + QPointF(60, 75), student.getOrderDate() + " №" + student.getOrderNumber());  // Значение поля

        painter.drawText(contentRect.topLeft() + QPointF(0, 90), "Дата выдачи ");          // Название поля
        painter.drawLine(contentRect.topLeft().x(), contentRect.topLeft().y() + 90 + smallBodyFontMetrics.ascent(),
                         contentRect.topLeft().x() + halfPageWidth / 2.2, contentRect.topLeft().y() + 90 + smallBodyFontMetrics.ascent()); // Линия под датой выдачи
        painter.drawText(contentRect.topLeft() + QPointF(60, 90), student.getIssueDate());  // Значение поля

        // Подписи оставляем пустыми, только линии под ними
        yPosition += 120;

        painter.setFont(smallInfoFont);
        QRectF horizontalSignatureRect(textStartX, yPosition -= 120, halfPageWidth, smallInfoFontMetrics.height());
        painter.drawText(horizontalSignatureRect.topLeft() + QPointF(0, 110), "Подпись студента:");  // Надпись "Подпись студента:"
        painter.drawLine(horizontalSignatureRect.topLeft().x(), horizontalSignatureRect.topLeft().y() + 110,
                         horizontalSignatureRect.topLeft().x() + halfPageWidth / 2.2, horizontalSignatureRect.topLeft().y() + 110);  // Линия под подписью студента

        QRectF verticalDirectorRect(10, yPosition - 120, halfPageWidth, smallInfoFontMetrics.lineSpacing() * 6);
        QString directorText = "Руководитель организации,\nосуществляющей\nобразовательную\nдеятельность, или иное\nуполномоченное имя,\nдолжностное лицо";
        painter.drawText(verticalDirectorRect, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap, directorText);  // Надпись "Руководитель..."
        painter.drawLine(verticalDirectorRect.topLeft().x(), verticalDirectorRect.bottomRight().y(),
                         verticalDirectorRect.topLeft().x() + halfPageWidth / 2.2, verticalDirectorRect.bottomRight().y());  // Линия под надписью "Руководитель..."

        yPosition += 250;
    }

    painter.end();
}
