#include "SfzFilter.h"
#include "ui_MainWindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <jack/jack.h>
#include <memory>

///
struct jack_delete {
    void operator()(jack_client_t *x) const noexcept { jack_client_close(x); }
};

typedef std::unique_ptr<jack_client_t, jack_delete> jack_client_u;

///
class DemoApp : public QApplication {
public:
    DemoApp(int &argc, char **argv);
    bool initSound();
    void initWindow();

private:
    static int processAudio(jack_nframes_t nframes, void *cbdata);

private:
    void valueChangedType(int value);
    void valueChangedCutoff(int value);
    void valueChangedResonance(int value);
    void valueChangedPkShGain(int value);

private:
    jack_client_u fClient;
    jack_port_t *fPorts[4] = {};
    SfzFilter<2> fFilter;

    QMainWindow *fWindow = nullptr;
    Ui::MainWindow fUi;

    static constexpr int cutoffMin = 10.0;
    static constexpr int cutoffMax = 20000.0;

    static constexpr int resoMin = 0.0;
    static constexpr int resoMax = 20.0;

    static constexpr int pkshMin = 0.0;
    static constexpr int pkshMax = 20.0;

    int fType = kSfzFilterNone;
    int fCutoff = cutoffMin;
    int fReso = resoMin;
    int fPksh = pkshMin;
};

DemoApp::DemoApp(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setApplicationName("Sfz Filters");
}

bool DemoApp::initSound()
{
    jack_client_t *client = jack_client_open(
        applicationName().toUtf8().data(), JackNoStartServer, nullptr);
    if (!client) {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot open JACK audio."));
        return false;
    }

    fClient.reset(client);

    fFilter.init(jack_get_sample_rate(client));

    fPorts[0] = jack_port_register(client, "in_left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    fPorts[1] = jack_port_register(client, "in_right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    fPorts[2] = jack_port_register(client, "out_left", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    fPorts[3] = jack_port_register(client, "out_right", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    if (!(fPorts[0] && fPorts[1] && fPorts[2] && fPorts[3])) {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot register JACK ports."));
        return false;
    }

    jack_set_process_callback(client, &processAudio, this);

    if (jack_activate(client) != 0) {
        QMessageBox::critical(nullptr, tr("Error"), tr("Cannot activate JACK client."));
        return false;
    }

    return true;
}

void DemoApp::initWindow()
{
    QMainWindow *window = new QMainWindow;
    fWindow = window;
    fUi.setupUi(window);

    QComboBox *cbTypes = fUi.comboBox;
    cbTypes->addItem("None", static_cast<int>(kSfzFilterNone));
    cbTypes->addItem("Apf1p", static_cast<int>(kSfzFilterApf1p));
    cbTypes->addItem("Bpf1p", static_cast<int>(kSfzFilterBpf1p));
    cbTypes->addItem("Bpf2p", static_cast<int>(kSfzFilterBpf2p));
    cbTypes->addItem("Bpf4p", static_cast<int>(kSfzFilterBpf4p));
    cbTypes->addItem("Bpf6p", static_cast<int>(kSfzFilterBpf6p));
    cbTypes->addItem("Brf1p", static_cast<int>(kSfzFilterBrf1p));
    cbTypes->addItem("Brf2p", static_cast<int>(kSfzFilterBrf2p));
    cbTypes->addItem("Hpf1p", static_cast<int>(kSfzFilterHpf1p));
    cbTypes->addItem("Hpf2p", static_cast<int>(kSfzFilterHpf2p));
    cbTypes->addItem("Hpf4p", static_cast<int>(kSfzFilterHpf4p));
    cbTypes->addItem("Hpf6p", static_cast<int>(kSfzFilterHpf6p));
    cbTypes->addItem("Lpf1p", static_cast<int>(kSfzFilterLpf1p));
    cbTypes->addItem("Lpf2p", static_cast<int>(kSfzFilterLpf2p));
    cbTypes->addItem("Lpf4p", static_cast<int>(kSfzFilterLpf4p));
    cbTypes->addItem("Lpf6p", static_cast<int>(kSfzFilterLpf6p));
    cbTypes->addItem("Pink", static_cast<int>(kSfzFilterPink));
    cbTypes->addItem("Lpf2pSv", static_cast<int>(kSfzFilterLpf2pSv));
    cbTypes->addItem("Hpf2pSv", static_cast<int>(kSfzFilterHpf2pSv));
    cbTypes->addItem("Bpf2pSv", static_cast<int>(kSfzFilterBpf2pSv));
    cbTypes->addItem("Brf2pSv", static_cast<int>(kSfzFilterBrf2pSv));
    cbTypes->addItem("Lsh", static_cast<int>(kSfzFilterLsh));
    cbTypes->addItem("Hsh", static_cast<int>(kSfzFilterHsh));

    cbTypes->setCurrentIndex(cbTypes->findData(fType));

    connect(
        cbTypes, QOverload<int>::of(&QComboBox::currentIndexChanged),
        this, [this, cbTypes](int index) { valueChangedType(cbTypes->itemData(index).toInt()); });

    fUi.dialCutoff->setRange(cutoffMin, cutoffMax);
    fUi.dialResonance->setRange(resoMin, resoMax);
    fUi.dialPkShGain->setRange(pkshMin, pkshMax);
    fUi.spinCutoff->setRange(cutoffMin, cutoffMax);
    fUi.spinResonance->setRange(resoMin, resoMax);
    fUi.spinPkShGain->setRange(pkshMin, pkshMax);

    fUi.dialCutoff->setValue(fCutoff);
    fUi.dialResonance->setValue(fReso);
    fUi.dialPkShGain->setValue(fPksh);
    fUi.spinCutoff->setValue(fCutoff);
    fUi.spinResonance->setValue(fReso);
    fUi.spinPkShGain->setValue(fPksh);

    connect(
        fUi.dialCutoff, &QDial::valueChanged,
        this, [this](int value) { valueChangedCutoff(value); });
    connect(
        fUi.spinCutoff, QOverload<int>::of(&QSpinBox::valueChanged),
        this, [this](int value) { valueChangedCutoff(value); });
    connect(
        fUi.dialResonance, &QDial::valueChanged,
        this, [this](int value) { valueChangedResonance(value); });
    connect(
        fUi.spinResonance, QOverload<int>::of(&QSpinBox::valueChanged),
        this, [this](int value) { valueChangedResonance(value); });
    connect(
        fUi.dialPkShGain, &QDial::valueChanged,
        this, [this](int value) { valueChangedPkShGain(value); });
    connect(
        fUi.spinPkShGain, QOverload<int>::of(&QSpinBox::valueChanged),
        this, [this](int value) { valueChangedPkShGain(value); });

    window->show();
}

int DemoApp::processAudio(jack_nframes_t nframes, void *cbdata)
{
    DemoApp *self = reinterpret_cast<DemoApp *>(cbdata);

    const float *ins[2];
    float *outs[2];

    ins[0] = reinterpret_cast<float *>(jack_port_get_buffer(self->fPorts[0], nframes));
    ins[1] = reinterpret_cast<float *>(jack_port_get_buffer(self->fPorts[1], nframes));
    outs[0] = reinterpret_cast<float *>(jack_port_get_buffer(self->fPorts[2], nframes));
    outs[1] = reinterpret_cast<float *>(jack_port_get_buffer(self->fPorts[3], nframes));

    self->fFilter.setType(static_cast<SfzFilterType>(self->fType));
    self->fFilter.process(ins, outs, self->fCutoff, self->fReso, self->fPksh, nframes);

    return 0;
}

void DemoApp::valueChangedType(int value)
{
    fType = value;
}

void DemoApp::valueChangedCutoff(int value)
{
    fUi.dialCutoff->blockSignals(true);
    fUi.dialCutoff->setValue(value);
    fUi.dialCutoff->blockSignals(false);

    fUi.spinCutoff->blockSignals(true);
    fUi.spinCutoff->setValue(value);
    fUi.spinCutoff->blockSignals(false);

    fCutoff = value;
}

void DemoApp::valueChangedResonance(int value)
{
    fUi.dialResonance->blockSignals(true);
    fUi.dialResonance->setValue(value);
    fUi.dialResonance->blockSignals(false);

    fUi.spinResonance->blockSignals(true);
    fUi.spinResonance->setValue(value);
    fUi.spinResonance->blockSignals(false);

    fReso = value;
}

void DemoApp::valueChangedPkShGain(int value)
{
    fUi.dialPkShGain->blockSignals(true);
    fUi.dialPkShGain->setValue(value);
    fUi.dialPkShGain->blockSignals(false);

    fUi.spinPkShGain->blockSignals(true);
    fUi.spinPkShGain->setValue(value);
    fUi.spinPkShGain->blockSignals(false);

    fPksh = value;
}

int main(int argc, char *argv[])
{
    DemoApp app(argc, argv);

    if (!app.initSound())
        return 1;

    app.initWindow();

    return app.exec();
}
