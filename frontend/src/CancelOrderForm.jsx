import { useState } from "react";

function CancelOrderForm({selectedStock,cancelOrderResponse,cancelOrder})
{
    const [orderId,setOrderId]=useState(100);
    const [side,setSide]=useState("BUY");
    

    return(
        <>
            <div>
                <h2>
                    Cancel Order
                </h2>
                
                <form>
                    <label htmlFor="oId">Order Id:</label>
                    <input value={orderId} onChange={(event)=>{
                        setOrderId(Number(event.target.value));
                    }}></input>
                    <br/>

                    <label htmlFor="side">Side:</label>
                    <select value={side} onChange={(event)=>
                        {
                            setSide(event.target.value);
                        }
                    }>
                        <option name="BUY">BUY</option>
                        <option name="SELL">SELL</option>
                    </select>
                    <br></br>
                    <button type="submit" onClick={(event)=>{
                        event.preventDefault();
                        const order={
                            orderId:orderId,
                            stockName:selectedStock,
                            side:side
                        }
                        cancelOrder(order);
                        
                    }}>Cancel Order</button>
                </form>
                
                <br/>
                <br/>
                <hr/>
                <pre>
                    {JSON.stringify(cancelOrderResponse,null,2)}
                </pre>
            </div>
        </>
    )
}

export default CancelOrderForm;