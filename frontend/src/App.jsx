import Card from "./components/Card.jsx"
import Header from "./Header.jsx";
import OrderBook from "./OrderBook.jsx";
import OrderForm from "./OrderForm.jsx";
import Statistics from "./Statistics.jsx";
import Trades from "./Trades.jsx";
import StockSelector from "./stockSelector.jsx";
import StressTestSelector from "./StressTestSelector.jsx"; 
import StressTestCancellationSelector from "./StressTestCancellationSelector.jsx";
import CancelOrderForm from "./CancelOrderForm.jsx";
import { useEffect, useState } from "react";

function App() {


   const [showOrderBook,setShowOrderBook]=useState(false);
  const [showTradeBook,setShowTradeBook]=useState(false);
  const [OrderBookData,setOrderBookData]=useState(null);
  const [tradeBookData,setTradeBookData]=useState(null);
  const [selectedStock,setSelectedStock]=useState("DairyMilk");
  const[placeOrderResponse,setPlaceOrderResponse]=useState(null);

  const[showStatistics,setShowStatistics]=useState(false);
  const[statsResponseData,setStatsResponseData]=useState(null);

  const[cancelOrderResponse,setCancelOrderResponse]=useState(null);

  const[stressResponse,setStressResponse]=useState(null);
  const[showStressTestResult,setShowStressTestResult]=useState(false);

  const[stressCancellationResponse,setStressCancellationResponse]=useState(null);
  const[showStressCancellationTestResult,setShowStressCancellationTestResult]=useState(false);

  useEffect(()=>
  {
    loadData();
    loadStatistics();
    loadTrades();

  },[selectedStock])


  async function loadData()
  {
    const response=await fetch(`${meta.env.VITE_API_URL}/orders/${selectedStock}`);
    const data=await response.json();
    setOrderBookData(data);
    setShowOrderBook(true);

  }

  async function placeOrder(order)
  {
    console.log(order);
    
    const response=await fetch(`${meta.env.VITE_API_URL}/placeOrder`,{
      method:"POST",
      headers:{
        "Content-Type":"application/json"
      },
      body:JSON.stringify(order)
    })
    const data=await response.json();
    setPlaceOrderResponse(data);
    loadData();
    loadStatistics();
    loadTrades();

  }

  async function loadTrades()
  {
    const response=await fetch(`${meta.env.VITE_API_URL}/trades/${selectedStock}`);
    const data=await response.json();
    setTradeBookData(data);
    setShowTradeBook(true);
    
  }

  async function loadStatistics()
  {
    const response=await fetch(`${meta.env.VITE_API_URL}/statistics/${selectedStock}`);
    const data=await response.json();

    setStatsResponseData(data);
    setShowStatistics(true);
  }

  async function cancelOrder(order)
  {
    const response=await fetch(`${meta.env.VITE_API_URL}/cancelOrder`,{
      method:"POST",
      headers:{
        "Content-Type":"application/json"
      },
      body:JSON.stringify(order)
    });
    const data=await response.json();
    setCancelOrderResponse(data);
    loadData();
    loadStatistics();
    loadTrades();
  }

  async function performStressTest(numberOfOrders)
  {
    const response=await fetch(`${meta.env.VITE_API_URL}/stressTest/${numberOfOrders}`);
    const data=await response.json();
    loadTrades();
    setStressResponse(data);
    setShowStressTestResult(!showStressTestResult);
    loadData();
    loadStatistics();
    loadTrades();


  }

  async function performStressCancellationTest(numberOfOrders)
  {
    const response=await fetch(`${meta.env.VITE_API_URL}/stressCancellationTest/${numberOfOrders}`);
    const data=await response.json();
    loadStatistics();
    setStressCancellationResponse(data);
    setShowStressCancellationTestResult(!showStressTestResult);
    loadData();
    loadStatistics();
    loadTrades();


  }
  return(
    <>
        <div className="min-h-screen bg-[#0B061B]">
          <Header />
            <div>
              <Card>
                <StockSelector selectedStock={selectedStock} setSelectedStock={setSelectedStock}/>
              </Card>
            </div>
            <div className="grid grid-cols-3 gap-2 p-4 mx-2 my-2 ">
              <Card>
                <h1 className="place-self-center text-2xl absolute">Order Entry</h1>
                
                <OrderForm placeOrder={placeOrder} selectedStock={selectedStock} placeOrderResponse={placeOrderResponse}/>
              </Card>
              <Card>
                <h1 className="place-self-center text-2xl">Order Book</h1>
                <OrderBook showOrderBook={showOrderBook} loadData={loadData} OrderBookData={OrderBookData}/>
              </Card>
              <Card>
                <h1 className="place-self-center text-2xl">Statistics</h1>
                <Statistics loadStatistics={loadStatistics} showStatistics={showStatistics} statsResponseData={statsResponseData}/>
              </Card>
            </div>

            <div className="grid grid-cols-2 gap-2 p-4 mx-2 my-2">
              <Card>
                <h1 className="place-self-center text-2xl">Recent Trades</h1>
                <Trades showTradeBook={showTradeBook} tradeBookData={tradeBookData} loadTrades={loadTrades}/>
              </Card>
              <Card>
                    <h1 className="place-self-center text-2xl">Cancel Order</h1>
                    <CancelOrderForm selectedStock={selectedStock} cancelOrderResponse={cancelOrderResponse} cancelOrder={cancelOrder}/>
              </Card>
              
            </div>
            <div className=" grid grid-cols-2 gap-2 p-4 mx-2 my-2 ">
              <Card>
                  <h1 className="place-self-center text-2xl">Market Simulator</h1>
                  <StressTestSelector performStressTest={performStressTest} stressResponse={stressResponse} showStressTestResult={showStressTestResult} tradeBookData={tradeBookData}/>
              </Card>
              <Card>
                  <h1 className="place-self-center text-2xl">Market Simulator with Cancellations</h1>
                  <StressTestCancellationSelector performStressCancellationTest={performStressCancellationTest} stressCancellationResponse={stressCancellationResponse} showStressCancellationTestResult={showStressCancellationTestResult} statsResponseData={statsResponseData}/>
              </Card>
             
            </div>

          
        </div>
    </>
  )
}

export default App;
