#include "hazukey_preedit.h"

#include "hazukey_candidate.h"
#include "hazukey_config.h"
#include "hazukey_state.h"

namespace fcitx {

constexpr int NormalCandidateListNBest = 18;
constexpr int PredictCandidateListNBest = 4;

std::string HazukeyPreedit::text() const {
    if (ic_->capabilityFlags().test(CapabilityFlag::Preedit)) {
        return ic_->inputPanel().clientPreedit().toString();
    } else {
        return ic_->inputPanel().preedit().toString();
    }
}

void HazukeyPreedit::setPreedit(Text text) {
    if (ic_->capabilityFlags().test(CapabilityFlag::Preedit)) {
        ic_->inputPanel().setClientPreedit(text);
    } else {
        ic_->inputPanel().setPreedit(text);
    }
}

void HazukeyPreedit::setSimplePreedit(const std::string &text) {
    std::vector<std::string> texts = {text};
    setMultiSegmentPreedit(texts, 0);
}

void HazukeyPreedit::setMultiSegmentPreedit(std::vector<std::string> &texts,
                                            int cursorSegment = 0) {
    auto preedit = Text();
    for (int i = 0; size_t(i) < texts.size(); i++) {
        if (i < cursorSegment) {
            preedit.append(texts[i], TextFormatFlag::NoFlag);
        } else if (i == cursorSegment) {
            preedit.setCursor(preedit.textLength());
            preedit.append(texts[i], TextFormatFlag::HighLight);
            continue;
        } else {
            preedit.append(texts[i], TextFormatFlag::Underline);
        }
    }
    setPreedit(preedit);
}

void HazukeyPreedit::commitPreedit() {
    if (ic_->capabilityFlags().test(CapabilityFlag::Preedit)) {
        ic_->commitString(
            ic_->inputPanel().clientPreedit().toStringForCommit());
    } else {
        ic_->commitString(ic_->inputPanel().preedit().toStringForCommit());
    }
}

}  // namespace fcitx