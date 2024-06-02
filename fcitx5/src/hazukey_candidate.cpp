#include "hazukey_candidate.h"

namespace fcitx {

std::vector<std::string> HazukeyCandidateWord::getPreedit() const {
    if (hiragana_.empty()) return {candidate_};
    return {candidate_, hiragana_};
}

void HazukeyCandidateWord::select(InputContext* ic) const {
    // 苦肉の策:
    // statesのリストの関数を呼び出せないので数字キーイベントを送って選択させる
    // createCandidateList系こっちに持ってきた方がいい
    // preeditCandidateListは効かない
    KeyEvent keyEvent(ic, Key(FcitxKey_Return));
    switch (index_ % 9) {
        case 0:
            keyEvent = KeyEvent(ic, Key(FcitxKey_1));
            break;
        case 1:
            keyEvent = KeyEvent(ic, Key(FcitxKey_2));
            break;
        case 2:
            keyEvent = KeyEvent(ic, Key(FcitxKey_3));
            break;
        case 3:
            keyEvent = KeyEvent(ic, Key(FcitxKey_4));
            break;
        case 4:
            keyEvent = KeyEvent(ic, Key(FcitxKey_5));
            break;
        case 5:
            keyEvent = KeyEvent(ic, Key(FcitxKey_6));
            break;
        case 6:
            keyEvent = KeyEvent(ic, Key(FcitxKey_7));
            break;
        case 7:
            keyEvent = KeyEvent(ic, Key(FcitxKey_8));
            break;
        case 8:
            keyEvent = KeyEvent(ic, Key(FcitxKey_9));
            break;
    }
    ic->keyEvent(keyEvent);
}

CandidateLayoutHint HazukeyCandidateList::layoutHint() const {
    return CandidateLayoutHint::Vertical;
}

void HazukeyCandidateList::focus(KeyList selectionKeys) {
    setPageSize(9);
    setSelectionKey(selectionKeys);
    setCursorIndex(0);
    focused_ = true;
}

const HazukeyCandidateWord& HazukeyCandidateList::getCandidate(
    int localIndex) const {
    return static_cast<const HazukeyCandidateWord&>(candidate(localIndex));
}

}  // namespace fcitx