#include "gmock/gmock.h"
#include <ranges>
using ::testing::ElementsAreArray;
using std::vector;
using std::optional;
using std::domain_error;

constexpr long long tribo(const int N, vector<optional<long long>> &memo) {
  // すでに計算済みならば解をリターン
  if (memo[N].has_value()) {
    return memo[N].value();
  }

  // ベースケース
  switch (N) {
    case 0:
    case 1: memo[N] = 0; break;
    case 2: memo[N] = 1; break;
    default:
      // 答えをメモ化しながら, 再帰呼び出し
      memo[N] = tribo(N - 1, memo) + tribo(N - 2, memo) + tribo(N - 3, memo);
      break;
  }

  return memo[N].value();
}


constexpr vector<long long> tribo_wrapper(const int N) {
  using std::views::transform;
  using std::ranges::to;

  if (N < 0) {
    throw domain_error("argument must not be negative");
  }

  // tribo(N) の解をメモ化する配列
  vector<optional<long long>> memo(N + 1);

  tribo(N, memo);

  // optionalはがし
  return memo | transform([](const auto o) { return o.value(); }) // TODO: optional<auto> or concept
              | to<vector>();
}

TEST(TestSuite, Test50) {
  EXPECT_THAT(tribo_wrapper(50), ElementsAreArray(vector<long long> {
    0,
    0,
    1,
    1,
    2,
    4,
    7,
    13,
    24,
    44,
    81,
    149,
    274,
    504,
    927,
    1'705,
    3'136,
    5'768,
    10'609,
    19'513,
    35'890,
    66'012,
    121'415,
    223'317,
    410'744,
    755'476,
    1'389'537,
    2'555'757,
    4'700'770,
    8'646'064,
    15'902'591,
    29'249'425,
    53'798'080,
    98'950'096,
    181'997'601,
    334'745'777,
    615'693'474,
    1'132'436'852,
    2'082'876'103,
    3'831'006'429,
    7'046'319'384,
    12'960'201'916,
    23'837'527'729,
    43'844'049'029,
    80'641'778'674,
    148'323'355'432,
    272'809'183'135,
    501'774'317'241,
    922'906'855'808,
    1'697'490'356'184,
    3'122'171'529'233,
  }));
}

TEST(TestSuite, Negative) {
  EXPECT_THROW(tribo_wrapper(-1), domain_error);
}
