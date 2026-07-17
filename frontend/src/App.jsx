import Header from "./Header.jsx"
import StockSelector from "./StockSelector.jsx"
import OrderForm from "./OrderForm.jsx"
import OrderBook from "./OrderBook.jsx"

import Trades from "./Trades.jsx"
import Statistics from "./Statistics.jsx"
import CancelOrderForm from "./CancelOrderForm.jsx"
import StressTestSelector from "./StressTestSelector.jsx"

import { useState } from "react"

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
  const[showStressTestResult,setShowStressTestResult]=useState(null);


  async function loadData()
  {
    const response=await fetch(`${import.meta.env.VITE_API_URL}/orders/${selectedStock}`);
    const data=await response.json();
    setOrderBookData(data);
    setShowOrderBook(true);

  }

  async function placeOrder(order)
  {
    console.log(order);
    
    const response=await fetch(`${import.meta.env.VITE_API_URL}/placeOrder`,{
      method:"POST",
      headers:{
        "Content-Type":"application/json"
      },
      body:JSON.stringify(order)
    })
    const data=await response.json();
    setPlaceOrderResponse(data);

  }

  async function loadTrades()
  {
    const response=await fetch(`${import.meta.env.VITE_API_URL}/trades/${selectedStock}`);
    const data=await response.json();
    setTradeBookData(data);
    setShowTradeBook(true);
    
  }

  async function loadStatistics()
  {
    const response=await fetch(`${import.meta.env.VITE_API_URL}/statistics/${selectedStock}`);
    const data=await response.json();

    setStatsResponseData(data);
    setShowStatistics(true);
  }

  async function cancelOrder(order)
  {
    const response=await fetch(`${import.meta.env.VITE_API_URL}/cancelOrder`,{
      method:"POST",
      headers:{
        "Content-Type":"application/json"
      },
      body:JSON.stringify(order)
    });
    const data=await response.json();
    setCancelOrderResponse(data);
  }

  async function performStressTest(numberOfOrders)
  {
    const response=await fetch(`${import.meta.env.VITE_API_URL}/stressTest/${numberOfOrders}`);
    const data=await response.json();
    setStressResponse(data);
    setShowStressTestResult(true);


  }

  

  return (
    <>
      <Header />
      <StockSelector selectedStock={selectedStock} setSelectedStock={setSelectedStock}/>
      <OrderForm placeOrder={placeOrder} selectedStock={selectedStock} placeOrderResponse={placeOrderResponse}/>
      <CancelOrderForm selectedStock={selectedStock} cancelOrderResponse={cancelOrderResponse} cancelOrder={cancelOrder}/>
      <OrderBook showOrderBook={showOrderBook} loadData={loadData} OrderBookData={OrderBookData}/>
      <Trades showTradeBook={showTradeBook} tradeBookData={tradeBookData} loadTrades={loadTrades}/>
      <Statistics loadStatistics={loadStatistics} showStatistics={showStatistics} statsResponseData={statsResponseData}/>
      <StressTestSelector performStressTest={performStressTest} stressResponse={stressResponse} showStressTestResult={showStressTestResult}/>
    </>
  )
}

export default App;
