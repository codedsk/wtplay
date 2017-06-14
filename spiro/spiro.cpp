#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WSpinBox>

using namespace Wt;

class SpirographApplication : public WApplication
{
public:
  SpirographApplication(const WEnvironment& env);

private:
  WSpinBox *n1_;
  WSpinBox *n2_;
  WSpinBox *n3_;

  void calculate_spirograph();
};

SpirographApplication::SpirographApplication(const WEnvironment& env)
  : WApplication(env)
{
  setTitle("Spirograph");

  WContainerWidget *container = new WContainerWidget(root());

  n1_ = new WSpinBox(container);
  n1_->setRange(-30,30);
  n1_->setValue(13);
  n1_->setSingleStep(1);

  n2_ = new WSpinBox(container);
  n2_->setRange(-30,30);
  n2_->setValue(-7);
  n2_->setSingleStep(1);

  n3_ = new WSpinBox(container);
  n3_->setRange(-30,30);
  n3_->setValue(-3);
  n3_->setSingleStep(1);

}

void SpirographApplication::calculate_spirograph()
{
}

WApplication *createApplication(const WEnvironment& env)
{
  return new SpirographApplication(env);
}

int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}


