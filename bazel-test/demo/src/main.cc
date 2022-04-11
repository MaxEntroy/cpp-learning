#include "demo/proto/ad_load.pb.h"

namespace demo {
void GenerateAdLoad(AdLoad* ad_load);
void ShowAdLoad(const AdLoad& ad_load);
}  // namespace demo


int main(void) {
  demo::AdLoad ad_load;
  GenerateAdLoad(&ad_load);
  ShowAdLoad(ad_load);
  return 0;
}

namespace demo {
void GenerateAdLoad(AdLoad* ad_load) {
  (*ad_load->mutable_ad_items())[3].set_id("20220321A301");
  (*ad_load->mutable_ad_items())[5].set_id("20220321A302");
  (*ad_load->mutable_ad_items())[8].set_id("20220321A302");
}
void ShowAdLoad(const AdLoad& ad_load) {
  for (auto it = ad_load.ad_items().begin(); it != ad_load.ad_items().end(); ++it) {
    std::cout << "pos:" << it->first << ", cmsid:" << it->second.id() << std::endl;
  }
}

}  // namespace demo
