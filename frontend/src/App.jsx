import Card from "./components/Card.jsx"
import Header from "./Header.jsx";
import OrderBook from "./OrderBook.jsx";
import OrderForm from "./OrderForm.jsx";
import Statistics from "./Statistics.jsx";
import { useState } from "react";
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
    const response=await fetch(`http://localhost:18000/orders/${selectedStock}`);
    const data=await response.json();
    setOrderBookData(data);
    setShowOrderBook(true);

  }

  async function placeOrder(order)
  {
    console.log(order);
    
    const response=await fetch(`http://localhost:18000/placeOrder`,{
      method:"POST",
      headers:{
        "Content-Type":"application/json"
      },
      body:JSON.stringify(order)
    })
    const data=await response.json();
    setPlaceOrderResponse(data);
    loadData();

  }

  async function loadTrades()
  {
    const response=await fetch(`http://localhost:18000/trades/${selectedStock}`);
    const data=await response.json();
    setTradeBookData(data);
    setShowTradeBook(true);
    
  }

  async function loadStatistics()
  {
    const response=await fetch(`http://localhost:18000/statistics/${selectedStock}`);
    const data=await response.json();

    setStatsResponseData(data);
    setShowStatistics(true);
  }

  async function cancelOrder(order)
  {
    const response=await fetch(`http://localhost:18000/cancelOrder`,{
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
    const response=await fetch(`http://localhost:18000/stressTest/${numberOfOrders}`);
    const data=await response.json();
    setStressResponse(data);
    setShowStressTestResult(true);


  }
  return(
    <>
        <div className="min-h-screen bg-[#0B061B]">
          <Header />
            <div className="grid grid-cols-3 gap-2 p-4 mx-2 my-2">
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
              </Card>
              <Card>
                  <h1 className="place-self-center text-2xl">Market Simulator</h1>
              </Card>
            </div>
            <div className="p-4 mx-2 my-2 ">
              <Card>
                    <h1 className="place-self-center text-2xl">Cancel Order</h1>
              </Card>
             
            </div>

          
        </div>
    </>
  )
}

export default App;
