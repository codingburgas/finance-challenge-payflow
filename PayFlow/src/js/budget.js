import axios from 'axios'; // Import the Axios library for making HTTP requests
const apiURL = 'http://localhost:18080/api/'

document.addEventListener("DOMContentLoaded", (event) => {
    let userId = localStorage.getItem('userId'); // Attempt to retrieve the 'userId' value from the browser's localStorage.
     // Check if 'userId' is invalid or missing
    if(userId == -1 || userId == null || userId == undefined || userId == "undefined")
    {
        location.replace('../index.html');
    }
});

document.getElementById("budgets").addEventListener("click", function(event) {
    debugger;
    // This code checks if the event target event.target exists and if it contains the class "delete-btn"
    if (event.target && event.target.classList.contains("delete-btn")) {
        const budgetItem = event.target.closest(".budget-item");
        // Check if a budget item was found
        if (budgetItem) {
            const budgetId = budgetItem.getAttribute("data-id");
            deleteBudget(budgetId);
        }
    }
});

initData();

function initData()
{
    getUserData();
    getBudgets();
}

document.getElementById('addBudgetForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    formJSON.userId = parseInt(localStorage.getItem('userId'));
    formJSON.id = parseInt(-1);
    formJSON.amount = parseInt(formJSON.amount);
    addBudget(formJSON);
});


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

function getBudgets()
{
     axios.get(apiURL + `budget/getByUser/${localStorage.getItem('userId')}`)
     .then(function (response) {
        if(response.status == 200)
         {
            const oldBudgets = document.querySelectorAll(".budget-item");
            oldBudgets.forEach(oldBudget => oldBudget.remove());
             if(response.data != null)
             {
                 console.log(response.data);

                 let budgets = response.data;
    
                 for(let i = 0;i<budgets.length;i++)
                 {
                     document.getElementById('budgets').innerHTML+=`
                         <div class="budget-item" data-id="${budgets[i].id}">
                            <div class="budget-info">
                                <div class="budget-icon"></div>
                                <span>${budgets[i].expenseType}</span>
                            </div>
                            <span>${budgets[i].amount} $</span>
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

function addBudget(body)
{
    axios.post(apiURL + 'budget/add', body)
    .then(function (response) {
        if(response.status == 200 || response.status == 204)
        {
            if(response != null)
            {
                console.log(response.data);
                getBudgets();
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

function deleteBudget(budgetId)
{
    axios.delete(apiURL + `budget/delete/${budgetId}`)
    .then(function (response) {
        debugger;
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log('budget deleted');
                getBudgets();

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