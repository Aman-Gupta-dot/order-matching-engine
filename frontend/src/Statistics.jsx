function Statistics({loadStatistics,showStatistics,statsResponseData})
{
    return (
        <>
            <div>
                <button onClick={()=>{
                    loadStatistics();
                }}>
                    View Statistics
                </button>

                <div>
                    <pre>
                        {JSON.stringify(statsResponseData,null,2)}
                    </pre>
                </div>
            </div>
        </>
    )
}

export default Statistics;