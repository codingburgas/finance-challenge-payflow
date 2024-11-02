import axios from 'axios';
import Chart from 'chart.js/auto';

const apiURL = 'http://localhost:18080/api/'

document.addEventListener("DOMContentLoaded", (event) => {
    let userId = localStorage.getItem('userId'); 
    if(userId == -1 || userId == null || userId == undefined || userId == "undefined")
    {
        location.replace('../index.html');
    }
});

initData();

function initData()
{
    getUserData();
    generateGraphs();

}

function getUserData()
{
    axios.get(apiURL + `user/getUserData/${localStorage.getItem('userId')}`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                document.getElementById('welcome-name').innerText = ` ${response.data.userName}`
            }
        }
        else
        {
            console.log(error);
            alert("Unauthorised");
        }
    })
    .catch(function (error) {
        console.log(error);
        alert("Fatal error");
    });
}

async function generateGraphs()
{
    debugger;
    const container = document.getElementById('budgetGraphs'); 
    const budgets = await axios.get(apiURL + `budget/getByUser/${localStorage.getItem('userId')}`);

    for(let i = 0;i<budgets.data.length;i++)
    {
        debugger;
        const canvasContainer = document.createElement("div");
        const canvasName = document.createElement("h1");
        const canvas = document.createElement("canvas");
        canvasName.classList.add('chartHeader');
        canvas.classList.add("chart");
        canvasContainer.appendChild(canvasName);
        canvasContainer.appendChild(canvas);
        container.appendChild(canvasContainer);

        try
        {
            const chartData = await axios.get(apiURL + `graph/getBudetGraph/${localStorage.getItem('userId')}/${budgets.data[i].expenseType}`)
            canvasName.innerText = budgets.data[i].expenseType;
            new Chart(canvas, {
                data: {
                datasets: [{
                    label: 'Budget',
                    data: chartData.data.budgetAmount,
                    type: 'line'
                },
                {
                    label: 'Amount',
                    data: chartData.data.sum,
                    type: 'bar'
                }
                ],
                labels: chartData.data.date,
    
                },
                options: {
                    borderColor: '#FFF100',
                    backgroundColor: '#7E60BF',
                    responsive: true,
                    legend: {
                        position: 'top',
                    },
                    title: {
                        display: true,
                        text: budgets.data[i].expenseType
                    },
                    animation: {
                        duration: 2000,
                        easing: 'easeOutBounce', 
                        delay: (context) => context.dataIndex * 200, 
                    },
                    hover: {
                        animationDuration: 500,
                    },
                }
            });    
        }
        catch(e){}   
    } 
}