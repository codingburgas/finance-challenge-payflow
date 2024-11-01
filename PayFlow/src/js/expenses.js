import axios from 'axios';
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
    const currentDate = new Date();
    const currentYear = currentDate.getFullYear();
    const currentMonth = currentDate.getMonth() + 1;
    getExpenses(currentYear, currentMonth);
    getUserData();
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
                    document.getElementById('successMessage').innerText = "Expense added successfully!";
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