import axios from 'axios';
const apiURL = 'http://localhost:18080/api/'
import Chart from 'chart.js/auto'

const expensesChart = document.getElementById('expenses-chart');

let barChart = null;

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
    const currentDate = new Date();
    const currentYear = currentDate.getFullYear();
    const currentMonth = currentDate.getMonth() + 1;
    getExpenses(currentYear, currentMonth);
    getUserData();
    initCharts();
}

function initCharts()
{
    initExpenseChart();
}


document.getElementById('expenseForm').addEventListener('submit', (event)=>{
    //debugger;
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    getExpenses(formJSON.year, formJSON.month);
});

document.getElementById('addExpenseForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    //debugger;
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    formJSON.userId = parseInt(localStorage.getItem('userId'));
    formJSON.date = `${formJSON.date} 00:00:00`;
    formJSON.id = parseInt(-1);
    formJSON.amount = parseInt(formJSON.amount);
    addExpenses(formJSON);
});

function getExpenses(year, month)
{
    axios.get(apiURL + `expense/getByUser/${localStorage.getItem('userId')}/${year}/${month}`)
    .then(function (response) {
        if(response.status == 200)
        {
           const oldExpenses = document.querySelectorAll(".expense-item");
           oldExpenses.forEach(oldExpense => oldExpense.remove());
            if(response.data != null)
            {
                console.log(response.data);

                let expenses = response.data;
                for(let i = 0;i<expenses.length;i++)
                {
                    document.getElementById('expenses').innerHTML+=`
                        <div class="expense-item">
                            <div class="expense-info">
                                <div class="expense-icon"></div>
                                <span>${expenses[i].type}</span>
                            </div>
                            <span>${expenses[i].amount} $</span>
                            <div class="transaction-icon1">
                            <span>${expenses[i].date}</span>
                            </div>
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

function addExpenses(body)
{
    axios.post(apiURL + 'expense/add', body)
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

function initExpenseChart()
{
    if(barChart != null)
    {
        barChart.destroy();
    }
    const context = expensesChart.getContext('2d');
    context.clearRect(0, 0, expensesChart.width, expensesChart.height);
    axios.get(apiURL + `graph/getExpenseGraph/${localStorage.getItem('userId')}`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log(response.data);

                barChart = new Chart(expensesChart, {
                    type: 'bar',
                    data: {
                      labels: response.data.date,
                      datasets: [{
                        label: 'Expenses',
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
                            text: 'Expenses'
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