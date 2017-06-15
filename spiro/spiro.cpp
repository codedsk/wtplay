#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WSpinBox>
#include <Wt/Chart/WCartesianChart>
#include <Wt/WStandardItemModel>
#include <cmath>
#include <complex>

#ifndef M_PI
#define M_PI std::acos(-1.0)
#endif

using namespace Wt;

class SpirographApplication : public WApplication
{
    public:
        SpirographApplication(const WEnvironment& env);

    private:
        WSpinBox *n1_;
        WSpinBox *n2_;
        WSpinBox *n3_;
        WStandardItemModel *model_;
        Chart::WCartesianChart *chart_;

        void calculate_spirograph();
};

SpirographApplication::SpirographApplication(const WEnvironment& env)
    : WApplication(env)
{
    setTitle("Spirograph");

    WContainerWidget *container = new WContainerWidget(root());

    // setup properties for gear #1
    n1_ = new WSpinBox(container);
    n1_->setRange(-30,30);
    n1_->setValue(13);
    n1_->setSingleStep(1);

    // setup properties for gear #2
    n2_ = new WSpinBox(container);
    n2_->setRange(-30,30);
    n2_->setValue(-7);
    n2_->setSingleStep(1);

    // setup properties for gear #3
    n3_ = new WSpinBox(container);
    n3_->setRange(-30,30);
    n3_->setValue(-3);
    n3_->setSingleStep(1);

    // store data from the spirograph calculations
    // in an item model as a table, 1000 items, 2 columns
    model_ = new WStandardItemModel(1000,2,container);
    model_->setHeaderData(0, WString("real(z)"));
    model_->setHeaderData(1, WString("imag(z)"));

    // create a chart to show the spirograph
    // column 0 is our X values
    // enable the legend
    chart_ = new Chart::WCartesianChart(container);
    chart_->setModel(model_);
    chart_->setXSeriesColumn(0);
    chart_->setLegendEnabled(true);

    // make it a scatterplot
    chart_->setType(Chart::ScatterPlot);

    // make the axes cross at 0
    chart_->axis(Chart::XAxis).setLocation(Chart::ZeroValue);
    chart_->axis(Chart::YAxis).setLocation(Chart::ZeroValue);

    // provide space for axis and title
    chart_->setPlotAreaPadding(120,Right);
    chart_->setPlotAreaPadding(40,Top|Bottom);

    // add the curve
    // column 1 holds our Y values for this curve
    Chart::WDataSeries *s = new Chart::WDataSeries(1,Chart::CurveSeries);
    s->setShadow(WShadow(3,3,WColor(0,0,0,127),3));
    chart_->addSeries(s);

    // set the default size of the chart
    // add vertical margins, center horizontally
    chart_->resize(800,300);
    chart_->setMargin(10,Top|Bottom);
    chart_->setMargin(WLength::Auto,Left|Right);

    // enable pan and zoom
    chart_->setPanEnabled(true);
    chart_->setZoomEnabled(true);

    // setup bindings for n1_, n2_, and n3_
    // when they are changed, recalculate the spirograph
    n1_->changed().connect(std::bind([=] () {
        calculate_spirograph();
    }));
    n2_->changed().connect(std::bind([=] () {
        calculate_spirograph();
    }));
    n3_->changed().connect(std::bind([=] () {
        calculate_spirograph();
    }));

    // setup an initial spirograph
    calculate_spirograph();

}

void SpirographApplication::calculate_spirograph()
{
    // run through the formula for calculating the points
    // in the spirograph using the equation:
    // t = linspace(0,1,1000)
    // z = exp(1i*2*pi*n1*t) + exp(1i*2*pi*n2*t) + exp(1i*2*pi*n3*t)
    // store the calculated data in our model_ object

    unsigned imin = 0;
    unsigned imax = 1;
    unsigned npts = 1000;
    double istep = 1.0*(imax-imin)/(npts-1);
    const std::complex<double> I(0.0,1.0);

    for (unsigned i = 0; i < npts; ++i) {
        double t = imin+(i*istep);
        std::complex<double> z =   std::exp((2*M_PI*n1_->value()*t)*I)
                                 + std::exp((2*M_PI*n2_->value()*t)*I)
                                 + std::exp((2*M_PI*n3_->value()*t)*I);
        model_->setData(i,0,z.real());
        model_->setData(i,1,z.imag());
    }
}

WApplication *createApplication(const WEnvironment& env)
{
    return new SpirographApplication(env);
}

int main(int argc, char **argv)
{
    return WRun(argc, argv, &createApplication);
}


