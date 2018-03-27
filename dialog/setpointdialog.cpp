#include "setpointdialog.h"
#include "ui_setpointdialog.h"

#include <QMessageBox>


SetPointDialog::SetPointDialog(shared_ptr<SceneObject> point, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPointDialog),
    ok(false)
{
    ui->setupUi(this);
    this->setWindowTitle("Настройка точки слежения");
    _point = point;

    ui->nameLineEdit->setText(_point->objectName());
    setColorWidget(_point->item()->color());

    switch (_point->tracker()->trackMethod())
    {
    case Template:
//        TemplateTracker *tracker = static_cast<TemplateTracker*>(_point->tracker());

//        ui->pointH->setValue(tracker->templateSize().h);
//        ui->pointW->setValue(tracker->templateSize().w);

//        ui->windowH->setValue(tracker->imageSize().h);
//        ui->windowW->setValue(tracker->imageSize().w);

//        bool enable = tracker->blur();
//        ui->spinBox_kernelSize->setEnabled(enable);
//        ui->doubleSpinBox_sigma->setEnabled(enable);
//        ui->label_8->setEnabled(enable);
//        ui->label_9->setEnabled(enable);

//        ui->checkBoxGauss->setChecked(enable);
//        ui->spinBox_kernelSize->setValue(tracker->kernelSize());
//        ui->doubleSpinBox_sigma->setValue(tracker->sigma());


//        ui->checkBoxGauss->setWhatsThis("Размытие по Гауссу - фильтр размытия изображения, "
//                                        "использующий нормальное распределение (также "
//                                        "называемое Гауссовым) для вычисления преобразования, "
//                                        "применяемого к каждому пикселю изображения.\n"
//                                        "Рекомендуется включить размытие для "
//                                        "снижения влияния шумов и увеличения "
//                                        "точности отслеживания точки.");
//        ui->spinBox_kernelSize->setWhatsThis("Размер должен быть нечетным и "
//                                             "находиться в пределах от 1 до 11.");
//        ui->doubleSpinBox_sigma->setWhatsThis("Рекомендуемое значение стандартного отклонения - "
//                                         "число в пределах от 0.5 до 5");
//        ui->label_8->setWhatsThis("Размер ядра определяет \"радиус\" размытия. "
//                                  "Чем больше ядро, тем сильнее изображение будет размыто.");
//        ui->label_9->setWhatsThis("Стандартное отклонение определяет степень "
//                                         "размытости каждой точки изображения. "
//                                         "Чем больше стандартное отклонение, тем сильнее "
//                                         "изображение будет размыто.");
//        break;

    case OpenCVLukasKanade:
        OpenCVTracker *tracker = static_cast<OpenCVTracker*>(_point->tracker());
        ui->maxLevel->setValue(tracker->maxLevel());
        ui->TCCount->setValue(tracker->TCCount());
        ui->TCEps->setValue(tracker->TCEps());
        ui->winSizeH->setValue(tracker->winSizeHeight());
        ui->winSizeW->setValue(tracker->winSizeWidth());

    //default:
    //    break;
    }
}

SetPointDialog::~SetPointDialog()
{
    delete ui;
}

void SetPointDialog::accept()
{
    if (ok)
        QDialog::accept();
}

void SetPointDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
    {
        QString name = ui->nameLineEdit->text();
        _point->setObjectName(name);
        _point->item()->graphicsItem()->setToolTip(name);

        _point->item()->setColor(ui->colorWidget->palette().color(QPalette::Background));

        switch (_point->tracker()->trackMethod())
        {
        case Template:
//            TemplateTracker *tracker = static_cast<TemplateTracker*>(_point->tracker());

//            if (ui->pointW->value() > ui->windowW->value() ||
//                    ui->pointH->value() > ui->windowH->value())
//            {
//                QMessageBox::warning(this, "Ошибка",
//                                     "Размер точки слежения не должен "
//                                     "превышать размер окна поиска!");
//                ok = false;
//            }
//            else
//            {
//                Size pointSize(ui->pointW->value(), ui->pointH->value());
//                Size windowSize(ui->windowW->value(), ui->windowH->value());

//                tracker->setTemplateSize(pointSize);
//                tracker->setImageSize(windowSize);

//                _point->item()->setSize(QSize(pointSize.w, pointSize.h));

//                ok = true;
//            }

//            if (ui->checkBoxGauss->isChecked())
//            {
//                _point->tracker()->setBlur(true);
//                double sigma = ui->doubleSpinBox_sigma->value();
//                int size = ui->spinBox_kernelSize->value();

//                if (size % 2 == 0)
//                {
//                    QMessageBox::warning(this, "Ошибка", "Размер ядра должен быть нечетным!");
//                    ok = false;
//                }
//                else
//                    _point->tracker()->setBlurParams(sigma, size);
//            }
//            else
//                _point->tracker()->setBlur(false);

//            break;
//       default:
//            break;

        case OpenCVLukasKanade:
            OpenCVTracker *tracker = static_cast<OpenCVTracker*>(_point->tracker());
            tracker->setMaxLevel(ui->maxLevel->value());
            tracker->setTermCriteria(ui->TCCount->value(), ui->TCEps->value());
            tracker->setWinSize(ui->winSizeW->value(), ui->winSizeH->value());
            ok = true;
        }
    }
}

//void SetPointDialog::on_checkBoxGauss_clicked()
//{
//    bool enable = ui->checkBoxGauss->isChecked();
//    ui->spinBox_kernelSize->setEnabled(enable);
//    ui->doubleSpinBox_sigma->setEnabled(enable);
//    ui->label_8->setEnabled(enable);
//    ui->label_9->setEnabled(enable);
//}

#include <QColorDialog>
void SetPointDialog::on_colorPushButton_clicked()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid())
        setColorWidget(color);
}

void SetPointDialog::setColorWidget(const QColor &color)
{
    QPalette Pal;
    Pal.setColor(QPalette::Background, color);
    ui->colorWidget->setAutoFillBackground(true);
    ui->colorWidget->setPalette(Pal);
    ui->colorWidget->setFrameStyle(1);
}
