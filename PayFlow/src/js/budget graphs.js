import axios from 'axios';  // Import the Axios library for making HTTP requests
import Chart from 'chart.js/auto';

const apiURL = 'http://localhost:18080/api/'

document.addEventListener("DOMContentLoaded", (event) => {
    let userId = localStorage.getItem('userId'); // Attempt to retrieve the 'userId' value from the browser's localStorage.
      // Check if 'userId' is invalid or missing
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
    // Make a GET request to retrieve user data based on the userId from localStorage
    axios.get(apiURL + `user/getUserData/${localStorage.getItem('userId')}`)
    .then(function (response) {
       // Code 200 is a standard HTTP status code that indicates that everything is in order and the request was completed successfully.
        if(response.status == 200) 
        {
            // If response.data is null, it means the API returned a response with no data or the information is not available.
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

// The asynchronous function allows operations that require time to be performed, such as retrieving data from an API
async function generateGraphs()
{
    debugger;
    const container = document.getElementById('budgetGraphs'); 
    const budgets = await axios.get(apiURL + `budget/getByUser/${localStorage.getItem('userId')}`);

    // Starts a loop that goes through each item in the budget data array
    for(let i = 0;i<budgets.data.length;i++)
    {
        debugger;
        const canvasContainer = document.createElement("div");
        const canvasName = document.createElement("h1");
        const canvas = document.createElement("canvas");
        canvasName.classList.add('chartHeader');
        canvas.classList.add("chart");
        canvasContainer.appendChild(canvasName); // This allows the graphic title to be part of the same container as the graphic itself
        canvasContainer.appendChild(canvas);
        container.appendChild(canvasContainer);

        try
        {
            // Wait is used to wait for the response from the server before moving on to the next code
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
                        delay: (context) => context.dataIndex * 200, // Delay introduces an animation delay for each element
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