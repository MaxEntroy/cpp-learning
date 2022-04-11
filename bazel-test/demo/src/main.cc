#include "demo/proto/ad_load.pb.h"

namespace demo {
void GenerateAdLoad(AdLoad* ad_load);
void ShowAdLoad(const AdLoad& ad_load);
}  // namespace demo


int main(void) {
  constexpr int kIterNum{10};
  for (int i = 0; i < kIterNum; ++i) {
    std::cout << "------------------ " << i + 1 << "th iter" << "------------------ " << std::endl;
    demo::AdLoad ad_load;
    GenerateAdLoad(&ad_load);
    ShowAdLoad(ad_load);
  }
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

/**
------------------ 1th iter------------------
pos:3, cmsid:20220321A301
pos:8, cmsid:20220321A302
pos:5, cmsid:20220321A302
------------------ 2th iter------------------
pos:3, cmsid:20220321A301
pos:8, cmsid:20220321A302
pos:5, cmsid:20220321A302
------------------ 3th iter------------------
pos:3, cmsid:20220321A301
pos:8, cmsid:20220321A302
pos:5, cmsid:20220321A302
------------------ 4th iter------------------
pos:5, cmsid:20220321A302
pos:3, cmsid:20220321A301
pos:8, cmsid:20220321A302
------------------ 5th iter------------------
pos:5, cmsid:20220321A302
pos:3, cmsid:20220321A301
pos:8, cmsid:20220321A302
------------------ 6th iter------------------
pos:8, cmsid:20220321A302
pos:3, cmsid:20220321A301
pos:5, cmsid:20220321A302
------------------ 7th iter------------------
pos:3, cmsid:20220321A301
pos:8, cmsid:20220321A302
pos:5, cmsid:20220321A302
------------------ 8th iter------------------
pos:5, cmsid:20220321A302
pos:3, cmsid:20220321A301
pos:8, cmsid:20220321A302
------------------ 9th iter------------------
pos:5, cmsid:20220321A302
pos:3, cmsid:20220321A301
pos:8, cmsid:20220321A302
------------------ 10th iter------------------
pos:5, cmsid:20220321A302
pos:3, cmsid:20220321A301
pos:8, cmsid:20220321A302
*/
