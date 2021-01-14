#include "HeaderView.h"

#include <QMenu>
#include <QStandardItemModel>
#include <QTimer>

#include "../Global.h"

namespace chongying {

void HeaderView::onSectionResized(const int &logicalIndex, const int &oldSize,
                                  const int &newSize) {
  Q_UNUSED(oldSize)
  if (newSize < this->minimumSectionSize()) return;
  this->model()->setHeaderData(logicalIndex, this->orientation(), newSize,
                               CyGlobal::SizeRole);
}

void HeaderView::contextMenu(const QPoint &point) {
  Q_UNUSED(point)
  QMenu menu;
  menu.addAction(tr("Auto size"), this, &HeaderView::autoSize);
  menu.addSeparator();

  for (int i = 0; i < this->sectionCount(); ++i) {
    const QString &text =
        this->model()
            ->headerData(i, this->orientation(), Qt::DisplayRole)
            .toString();
    const bool &hide =
        this->model()
            ->headerData(i, this->orientation(), CyGlobal::HideRole)
            .toBool();
    QAction *const action = menu.addAction(text);
    if (!i) action->setEnabled(false);
    action->setCheckable(true);
    action->setChecked(!hide);
    connect(action, &QAction::toggled, [this, i](bool checked) {
      this->setSectionHidden(i, !checked);
      this->model()->setHeaderData(i, this->orientation(), !checked,
                                   CyGlobal::HideRole);
      if (checked) {
        int size = this->model()
                       ->headerData(i, this->orientation(), CyGlobal::SizeRole)
                       .toInt();
        if (size >= this->minimumSectionSize()) {
          this->resizeSection(i, size);
        } else {
          this->resizeSection(i, this->sectionSizeHint(i));
        }
      }
    });
  }
  menu.exec(QCursor::pos());
}

int HeaderView::sectionCount() const {
  switch (this->orientation()) {
    case Qt::Horizontal:
      return this->model()->columnCount();
    case Qt::Vertical:
      return this->model()->rowCount();
  }
  return 0;
}

HeaderView::HeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent) {
  this->setSectionsMovable(true);
  this->setDefaultAlignment(Qt::AlignLeft);
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &QHeaderView::sectionResized, this,
          &HeaderView::onSectionResized);
  connect(this, &QHeaderView::customContextMenuRequested, this,
          &HeaderView::contextMenu);
}

void HeaderView::setModel(QAbstractItemModel *model) {
  QHeaderView::setModel(model);
  QTimer::singleShot(0, this, &HeaderView::refresh);
}

void HeaderView::autoSize() noexcept {
  if (!this->model()) return;
  this->resizeSections(QHeaderView::ResizeToContents);
  // 分配剩余空间
  const int &total_size = this->width() - this->length();
  if (total_size <= 0) return;
  const int &count = this->sectionCount();
  if (count <= 0) return;

  QVector<int> weights(count);
  int total_weight = 0;
  Qt::Orientation orientation = this->orientation();
  for (int i = 0; i < count; ++i) {
    int weight =
        this->model()->headerData(i, orientation, CyGlobal::FillRole).toInt();
    if (!this->model()
             ->headerData(i, orientation, CyGlobal::HideRole)
             .toBool()) {
      weights[i] = weight;
      total_weight += weight;
    }
  }

  if (total_weight <= 0) return;
  int used_size = 0;
  int last_index = -1;
  for (int i = 0; i < count; ++i) {
    if (weights[i] > 0) {
      last_index = i;
      int width = int((double(weights[i]) / total_weight) * total_size);
      used_size += width;
      this->resizeSection(i, width + this->sectionSize(i));
    }
  }
  int last_size = total_size - used_size;
  if (last_index >= 0 && last_size > 0)
    this->resizeSection(last_index, this->sectionSize(last_index) + last_size);
}

void HeaderView::refresh() noexcept {
  if (!this->model()) return;
  for (int i = 0; i < this->sectionCount(); ++i) {
    int size = this->model()
                   ->headerData(i, this->orientation(), CyGlobal::SizeRole)
                   .toInt();
    if (size >= this->minimumSectionSize()) {
      this->resizeSection(i, size);
    } else {
      this->resizeSection(i, this->sectionSizeHint(i));
    }
    bool hide = this->model()
                    ->headerData(i, this->orientation(), CyGlobal::HideRole)
                    .toBool();
    this->setSectionHidden(i, hide);
  }
}

}  // namespace chongying
