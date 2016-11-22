/**
 * test program for our ProductServices
 */

#include <iostream>
#include "products.hpp"
#include "productservice.hpp"

using namespace std;

int main()
{
  // Create the 10Y treasury note
  date maturityDate(2026, Nov, 16);
  string cusip = "912828M56";
  Bond treasuryBond(cusip, CUSIP, "T", 2.25, maturityDate);

  // Create the 2Y treasury note
  date maturityDate2(2018, Nov, 5);
  string cusip2 = "912828TW0";
  Bond treasuryBond2(cusip2, CUSIP, "T", 0.75, maturityDate2);

  // Create a BondProductService
  BondProductService *bondProductService = new BondProductService();

  // Add the 10Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond);
  Bond bond = bondProductService->GetData(cusip);
  cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

  // Add the 2Y note to the BondProductService and retrieve it from the service
  bondProductService->Add(treasuryBond2);
  bond = bondProductService->GetData(cusip2);
  cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

  // Create the Spot 10Y Outright Swap
  date effectiveDate(2016, Nov, 16);
  date terminationDate(2026, Nov, 16);
  string outright10Y = "Spot-Outright-10Y";
  IRSwap outright10YSwap(outright10Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate, terminationDate, USD, 10, SPOT, OUTRIGHT);

  // Create the IMM 2Y Outright Swap
  date effectiveDate2(2016, Dec, 20);
  date terminationDate2(2018, Dec, 20);
  string imm2Y = "IMM-Outright-2Y";
  IRSwap imm2YSwap(imm2Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate2, terminationDate2, USD, 2, IMM, OUTRIGHT);

  // Create a IRSwapProductService
  IRSwapProductService *swapProductService = new IRSwapProductService();

  // Add the Spot 10Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(outright10YSwap);
  IRSwap swap = swapProductService->GetData(outright10Y);
  cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

  // Add the IMM 2Y Outright Swap to the IRSwapProductService and retrieve it from the service
  swapProductService->Add(imm2YSwap);
  swap = swapProductService->GetData(imm2Y);
  cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

////////////////////////////////////////////
  cout << "*****************************" << endl;
  cout << "Ex2: " << endl;

  // Create several Futures
  date maturityDate3(2016, Dec, 12);
  string futureID1 = "future1";
  Future future(futureID1, EURODOLLARFUTURE, maturityDate);
  string futureID2 = "future2";
  Future future2(futureID2, EURODOLLARFUTURE, maturityDate2);
  string futureID3 = "future3";
  Future future3(futureID3, BONDFUTURE, maturityDate3);

  // Add to the FutureProductService
  FutureProductService *futureService = new FutureProductService();
  futureService->Add(future);
  Future ft = futureService->GetData(futureID1);
  cout << "Future: " << ft.GetProductId() << " == > " <<
    ft << endl;
  futureService->Add(future2);
  ft = futureService->GetData(futureID2);
  cout << "Future: " << ft.GetProductId() << " == > " <<
    ft << endl;
  futureService->Add(future3);
  ft = futureService->GetData(futureID3);
  cout << "Future: " << ft.GetProductId() << " == > " <<
    ft << endl;

////////////////////////////////////////////
  cout << "*****************************" << endl;
  cout << "Ex3: " << endl;

  // Add more bonds in BondProductService
  string cusip3 = "912828M58";
  Bond treasuryBond3(cusip3, CUSIP, "K", 4.25, maturityDate);
  string cusip4 = "912828TW1";
  Bond treasuryBond4(cusip4, CUSIP, "T", 1.75, maturityDate2);
  bondProductService->Add(treasuryBond3);
  bondProductService->Add(treasuryBond4);

  // test GetBonds function
  string ticker = "T";
  auto bondVec = bondProductService->GetBonds(ticker);
  for(auto& bd: bondVec) {
    cout << "CUSIP: " << bd.GetProductId() << " ==> " << bd << endl;
  }
  cout << endl;

  return 0;
}
