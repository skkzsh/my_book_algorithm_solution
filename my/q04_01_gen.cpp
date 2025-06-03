#include "gmock/gmock.h"
#include <generator>
using ::testing::ElementsAreArray;

std::generator<long long> tribo_generator() {
  using std::tie;
  using std::tuple;

  for (long long a = 0, b = 0, c = 1 ;; tie(a, b, c) = tuple{b, c, a + b + c}) {
    co_yield a;
  }
}

TEST(TestSuite, Test50) {
  using std::views::take;
  using std::ranges::to;
  using std::vector;

  constexpr int N = 51;

  EXPECT_THAT(tribo_generator() | take(N) | to<vector>(),
    ElementsAreArray(vector<long long> {
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
    })
  );
}
