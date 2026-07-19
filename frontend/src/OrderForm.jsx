import { useEffect, useState } from "react";

function OrderForm({placeOrder,selectedStock,placeOrderResponse}){
    const[side,setSide]=useState("BUY");
    const[type,setType]=useState("LIMIT");
    const[price,setPrice]=useState(0);
    const[quantity,setQuantity]=useState(0);

    
    
    return (
        <>
        <div className=" ">
            
            <div>
                <form className=" p-4  flex flex-col justify-between items-center w-full h-full ">
                   
                            
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
                   
                
                    
                            <div className="flex items-center justify-center gap-3 m-1 ">
                                        
                                        <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                        {
                                            
                                            setType("LIMIT");
                                        }}>
                                        {type=="LIMIT" && (<div className="w-2 h-2 rounded-full bg-white"></div>)}
                                        
                                         LIMIT
                                    </button>
                                    
                                    <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                    {
                                        
                                        setType("MARKET");
                                    }}>
                                    {type=="MARKET" && (<div className="w-2 h-2 rounded-full bg-white"></div>)}
                                        MARKET
                                    </button>
                                     <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                    {
                                        
                                        setType("FOK");
                                    }}>
                                    {type=="FOK" && (<div className="w-2 h-2 rounded-full bg-white"></div>)}
                                        FOK
                                    </button>
                                     <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                    {
                                        
                                        setType("IOC");
                                    }}>
                                    {type=="IOC" && (<div className="w-2 h-2 rounded-full bg-white"></div>)}
                                        IOC
                                    </button>
                            </div>
                    
                

                    
                                <div className="flex flex-col gap-1.5 mb-4 w-full">
                                            <label className="text-xs font-medium text-gray-400 uppercase" htmlFor="Price ">Price:</label>
                                    <input className="w-full bg-[#121124] text-white border border-gray-800  rounded-xl px-4 py-2.5" type="number" value={price} onChange={(event)=>{
                                        setPrice(Number(event.target.value));
                                    }}></input>
                                </div>
                    
                
                    
                                <div className="flex flex-col gap-1.5 mb-4 w-full">
                                            <label className="text-xs font-medium text-gray-400 uppercase"  htmlFor="Quantity">Quantity:</label>
                                    <input className="w-full bg-[#121124] text-white border border-gray-800  rounded-xl px-4 py-2.5" type="number" value={quantity} onChange={(event)=>{
                                        setQuantity(Number(event.target.value));
                                    }}></input>
                                </div>
                    
                    

                    
                                <button className=" flex justify-between items-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="submit" onClick={(event)=>{
                                event.preventDefault();
                                    const order={
                                        stockName:selectedStock,
                                        side:side,
                                        type:type,
                                        price:price,
                                        quantity:quantity
                                    }
                                    placeOrder(order);
                            }}>
                            
                            PLACE ORDER
                            </button>
                    
                </form>
                
                
            </div>

            <div>
                <h1>{ placeOrderResponse!=null && placeOrderResponse.msg}</h1>
            </div>
           
        </div> 
        </>
    )
}

export default OrderForm;