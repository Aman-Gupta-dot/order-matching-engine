import { useEffect, useState } from "react";

function Header()


{
    const[date,setDate]=useState(new Date().toLocaleTimeString("en-IN",{timeZone:"Asia/Kolkata",hour:"2-digit",minute:"2-digit",second:"2-digit"}));
    
    useEffect(()=>{//TO KEEP THE TIME CLOCKING
        const timer=setInterval(()=>{
            setDate(new Date().toLocaleTimeString("en-IN",{timeZone:"Asia/Kolkata",hour:"2-digit",minute:"2-digit",second:"2-digit"}));
        },1000);
        
        return ()=>clearInterval(timer);
    },[])
    return(
        <>
            <div className="bg-[#130B2A] text-white flex justify-between items-center h-25 w-full p-6">
                <h1 className="text-xl">Mercurus Exchange</h1>

                <div className="flex items-center gap-2">
                    <div className="w-4 h-4 rounded-full bg-green-500 ">
                    </div>
                    <div>
                        <h1 className="text-xl">Connected</h1>
                    </div>
                    <div className="text-xl">{date}</div>
                </div>
            </div>
        </>
    )
}
export default Header;