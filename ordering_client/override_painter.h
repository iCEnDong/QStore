#ifndef OVERRIDE_PAINTER_H
#define OVERRIDE_PAINTER_H

#include <QStyledItemDelegate>
#include <QPainter>

// 自定义委托用于显示图片,父类为QTableView
class ImageDelegate : public QStyledItemDelegate {
public:
    explicit ImageDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    // 重写QStyledItemDelegate::paint
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        // 默认当前单元格存放图片的地址,故直接获取
        QString imagePath = index.data(Qt::DisplayRole).toString();
        QPixmap pixmap(imagePath); // 生成图片类对象

        if (!pixmap.isNull()) {
            // 在单元格中绘制图片
            painter->save(); // 将当前画工状态压入堆栈

            // 计算图片的显示区域,保持图片的长宽比
            QRect displayRect = option.rect;

            // 计算合适的图片缩放尺寸
            QSize imageSize = pixmap.size();
            float imageAspect = static_cast<float>(imageSize.width()) / imageSize.height();
            float cellAspect = static_cast<float>(displayRect.width()) / displayRect.height();

            if(imageAspect > cellAspect) {
                // 图片比单元格更宽,保持宽度适配
                displayRect.setHeight(displayRect.width() / imageAspect);
                displayRect.moveTop((option.rect.height() - displayRect.height()) / 2 + option.rect.top());
            }else {
                // 图片比单元格更高,保持高度适配
                displayRect.setWidth(displayRect.height() * imageAspect);
                displayRect.moveLeft((option.rect.width() - displayRect.width()) / 2 + option.rect.left());
            }

            // 画图,使用平滑缩放
            painter->drawPixmap(displayRect, pixmap.scaled(displayRect.size(),
                                                           Qt::KeepAspectRatio,
                                                           Qt::SmoothTransformation));

            painter->restore(); // 弹栈
        } else {
            // 如果路径无效，默认保持绘制最初的文本
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
};

#endif // OVERRIDE_PAINTER_H
