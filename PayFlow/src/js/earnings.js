import axios from 'axios'; // Import Axios for making HTTP requests
const apiURL = 'http://localhost:18080/api/'
import Chart from 'chart.js/auto' // Import Chart.js for displaying charts

const earningsChart = document.getElementById('earnings-chart');

let barChart = null;

// Check if user is logged in when the DOM is fully loaded
document.addEventListener("DOMContentLoaded", (event) => {
    let userId = localStorage.getItem('userId'); 
    if(userId == -1 || userId == null || userId == undefined || userId == "undefined")
    {
        location.replace('../index.html');
    }
});

// Event listener for delete button clicks within the earnings list
document.getElementById("earnings").addEventListener("click", function(event) {
    debugger;
    if (event.target && event.target.classList.contains("delete-btn")) {
        const earningItem = event.target.closest(".earning-item");
        if (earningItem) {
            const earningId = earningItem.getAttribute("data-id");
            deleteEarning(earningId);
        }
    }
});

// Fetch and display earnings for a specific month and year when form is submitted
document.getElementById('earningForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    getEarnings(formJSON.year, formJSON.month);
});

// Handle the submission of adding a new earning
document.getElementById('addEarningForm').addEventListener('submit', (event)=>{
   event.preventDefault();
    debugger;
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    // Format the data
    formJSON.userId = parseInt(localStorage.getItem('userId'));
    formJSON.date = `${formJSON.date} 00:00:00`;
    formJSON.id = parseInt(-1);
    formJSON.amount = parseInt(formJSON.amount);
    addEarnings(formJSON);
});

initData();

// Initialize the data for the current user and populate page elements
function initData()
{
    const currentDate = new Date(); // new Date() automatically sets the current time, today's date and time
    const currentYear = currentDate.getFullYear();
    // The getMonth() method returns the index of the month where January is 0
    const currentMonth = currentDate.getMonth() + 1;
    getEarnings(currentYear, currentMonth);
    getUserData();
    initCharts();
}

// Initialize earnings chart
function initCharts()
{
    initEarningChart();
}

function getEarnings(year, month)
{
    axios.get(apiURL + `earning/getByUser/${localStorage.getItem('userId')}/${year}/${month}`)
    .then(function (response) {
        if(response.status == 200)
        {
        debugger;
           const oldEarnings = document.querySelectorAll(".earning-item");
           oldEarnings.forEach(oldEarning => oldEarning.remove());
            if(response.data != null)
            {
                console.log(response.data);

                let earnings = response.data;
                for(let i = 0;i<earnings.length;i++)
                {
                    document.getElementById('earnings').innerHTML+=`
                        <div class="earning-item" data-id="${earnings[i].id}"> // Will retrieve the ID of the current element from the array
                            <div class="earning-info">
                                <div class="earning-icon"></div>
                                <span>${earnings[i].type}</span>
                            </div>
                                <span>${earnings[i].amount} $</span>
                            <div class="transaction-icon1">
                                <span>${earnings[i].date}</span>
                            </div>
                            <button class="delete-btn" type="button">Delete</button>
                        </div>
                    `;
                }
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

// Add a new earning to the database
function addEarnings(body)
{
    axios.post(apiURL + 'earning/add',  )
    .then(function (response) {
        if(response.status == 200 || response.status == 204)
        {
            if(response != null)
            {
                console.log(response.data);
                if(response.data.userId != -1)
                {
                    document.getElementById('successMessage').innerText;
                }
                else
                {
                    alert("Unauthorised");
                }
                initData();
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

// Retrieve user data to personalize page (e.g., welcome message)
function getUserData()
{
    axios.get(apiURL + `user/getUserData/${localStorage.getItem('userId')}`)
    .then(function (response) {
        debugger;
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

// Initialize earnings chart using Chart.js and populate with data from API
function initEarningChart()
{
    if(barChart != null)
    {
        barChart.destroy();
    }
    const context = earningsChart.getContext('2d'); // Used to draw graphs
    context.clearRect(0, 0, earningsChart.width, earningsChart.height); // Schedule update
    axios.get(apiURL + `graph/getEarningGraph/${localStorage.getItem('userId')}`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log(response.data);

                barChart = new Chart(earningsChart, {
                    type: 'bar',
                    data: {
                      labels: response.data.date,
                      datasets: [{
                        label: 'Earnings',
                        data: response.data.sum,
                        borderWidth: 1,
                      }]
                    },
                    options: {
                        borderColor: '#F9E400',
                        backgroundColor: '#C65BCF',
                        legend: {
                            position: 'top',
                          },
                          title: {
                            display: true,
                            text: 'Earnings'
                          },
                      scales: {
                        y: {
                          beginAtZero: true
                        }
                      },
                      animation: {
                        duration: 2000,
                        easing: 'easeOutBounce', 
                        delay: (context) => context.dataIndex * 200, 
                        onProgress: (animation) => {
                            console.log('Animation Progress:', animation.currentStep / animation.numSteps);
                        },
                        onComplete: () => {
                            console.log('Animation Complete');
                        }
                    },
                    hover: {
                        animationDuration: 500,
                    },
                    }
                });         
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


// Delete earning by ID
function deleteEarning(earningId)
{
    axios.delete(apiURL + `earning/delete/${earningId}`)
    .then(function (response) {
        debugger;
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log('earning deleted');
                initData();
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