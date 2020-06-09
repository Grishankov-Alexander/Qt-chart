#ifndef PIEVIEW_H
#define PIEVIEW_H

#include <QAbstractItemView>


class PieView : public QAbstractItemView
{
    Q_OBJECT

public:
    PieView(QWidget *parent = nullptr);

    QRect visualRect(const QModelIndex &index) const override;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
    QModelIndex indexAt(const QPoint &point) const override;

protected slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>()) override;
    void rowsInserted(const QModelIndex &parent, int start, int end) override;
    void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end) override;

protected:
    bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event) override;
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    int horizontalOffset() const override;
    int verticalOffset() const override;
    bool isIndexHidden(const QModelIndex &index) const override;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void scrollContentsBy(int dx, int dy) override;
    QRegion visualRegionForSelection(const QItemSelection &selection) const override;

private:
    QRect itemRect(const QModelIndex &item) const;
    QRegion itemRegion(const QModelIndex &index) const;
    int rows(const QModelIndex &index = QModelIndex()) const;
    void updateGeometries() override;

    int margin = 0;
    int totalSize = 300;
    int pieSize = totalSize - 2*margin;
    int validItems = 0;
    double totalValue = 0.0;
    QRubberBand *rubberBand = nullptr;
    QPoint origin;
};

#endif // PIEVIEW_H
