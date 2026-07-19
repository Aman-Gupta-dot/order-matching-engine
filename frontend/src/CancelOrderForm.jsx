import { useState } from "react";

function CancelOrderForm({selectedStock,cancelOrderResponse,cancelOrder})
{
    const [orderId,setOrderId]=useState(100);
    const [side,setSide]=useState("BUY");
    

    return(
        <>
            <div>
                
                <form>
                    

                    <div className="flex flex-col gap-1.5 mb-4 w-full">

                    <label className="text-xs font-medium text-gray-400" htmlFor="Orders">Order Id:</label>
                    <input className="w-full bg-[#121124] text-white border border-gray-800  rounded-xl px-4 py-2.5" type="number"  onChange={(event)=>{
                        setOrderId(Number(event.target.value));
                    }}></input>

                </div>
                    <div className="flex items-center  gap-15 m-1">
                                        
                                        <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                        {
                                            
                                            setSide("BUY");
                                        }}>
                                        {side=="BUY" && (<div className="w-2 h-2 rounded-full bg-green-500"></div>)}
                                        
                                         BUY
                                    </button>
                                    
                                    <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                    {
                                        
                                        setSide("SELL");
                                    }}>
                                    {side=="SELL" && (<div className="w-2 h-2 rounded-full bg-red-500"></div>)}
                                        SELL
                                    </button>
                            </div>
                   
                    <br></br>
                    <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="submit" onClick={(event)=>{
                        event.preventDefault();
                        const order={
                            orderId:orderId,
                            stockName:selectedStock,
                            side:side
                        }
                        cancelOrder(order);
                        
                    }}>Cancel Order</button>
                </form>
                
                
            </div>

            <div>
                {cancelOrderResponse!=null && 
                    <div className="space-y-5 ">
                         <div className="flex justify-between">
                                    <span>Status:</span>
                                    <span>{cancelOrderResponse.status}</span>
                                </div>
                                

                                <div className="flex justify-between">
                                    <span>Message:</span>
                                    <span>{cancelOrderResponse.msg}</span>
                                </div>
                    </div>
                }
            </div>
        </>
    )
}

export default CancelOrderForm;