import { useState } from "react";

function StressTestSelector({performStressTest,stressResponse,showStressTestResult})
{
    const [randomOrders,setRandomOrders]=useState(100);
    return(
        <>
            <div>

            <label htmlFor="Orders">Enter No of Orders to Generate</label>
            <input value={randomOrders} onChange={(event)=>{
                setRandomOrders(Number(event.target.value));
            }}></input>
            <br></br>
            <button type="submit" onClick={(event)=>{
                event.preventDefault();
                performStressTest(randomOrders);
            }}>Generate</button>
            </div>
            <div>
                <pre>
                    {JSON.stringify(stressResponse,null,2)}
                </pre>
            </div>
        </>
    )
}
export default StressTestSelector;