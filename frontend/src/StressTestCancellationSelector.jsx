import { useState } from "react";

function StressTestCancellationSelector({performStressCancellationTest,stressCancellationResponse,showStressTestResult,statsResponseData})
{
    const [randomOrders,setRandomOrders]=useState(100);
    const[needRandomCancellations,setNeedRandomCancellations]=useState(false);
    return(
        <>
            <div className="flex flex-col">

                <div className="flex flex-col gap-1.5 mb-4 w-full">

                    <label className="text-xs font-medium text-gray-400" htmlFor="Orders">Number Of Orders</label>
                    <input className="w-full bg-[#121124] text-white border border-gray-800  rounded-xl px-4 py-2.5" type="number" value={randomOrders} onChange={(event)=>{
                        setRandomOrders(Number(event.target.value));
                    }}></input>

                </div>

               


        
             <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                    { 
                                        performStressCancellationTest(randomOrders);
                                    }}>
                                    Do Stress Cancellation Test
                                    </button>

            
            </div>
            <div>
                <div className="space-y-5 ">
                            <h2 className="text-xl font-bold">
                                Simulator Result
                            </h2>
                            
                            {stressCancellationResponse!=null && <div>

                                <div className="flex justify-between">
                                    <span>Orders Generated:</span>
                                    <span>{randomOrders}</span>
                                </div>
                                

                                <div className="flex justify-between">
                                    <span>Duration:</span>
                                    <span>{stressCancellationResponse.duration/1000}ms</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Orders Cancelled</span>
                                    <span>{statsResponseData.ordersCancelled}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Throughput:</span>
                                    <span>{randomOrders*1000000/stressCancellationResponse.duration} orders/sec</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Integrity Status:</span>
                                    <span>{stressCancellationResponse.IntegrityStatus}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>msg:</span>
                                    <span>{stressCancellationResponse.msg}</span>
                                </div>
                                
                            </div>}
                    </div>
            </div>
        </>
    )
}
export default StressTestCancellationSelector;