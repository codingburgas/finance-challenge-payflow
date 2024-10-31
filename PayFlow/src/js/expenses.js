import axios from 'axios';
const apiURL = 'http://localhost:18080/api/'

initData();

function initData()
{
    const currentDate = new Date();
    const currentYear = currentDate.getFullYear();
    const currentMonth = currentDate.getMonth() + 1;
    getExpenses(currentYear, currentMonth);
}


document.getElementById('expenseForm').addEventListener('submit', (event)=>{
    debugger;
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    createExpense(formJSON.year, formJSON.month);
});

function getExpenses(year, month)
{
    axios.get(apiURL + `expense/getByUser/${localStorage.getItem('userId')}/${year}/${month}`)
    .then(function (response) {
        if(response.status == 200)
        {

        const oldExpenses = document.querySelectorAll(".transaction");
        oldExpenses.forEach(oldExpense => oldExpense.remove());
            if(response.data != null)
            {
                console.log(response.data);

                let expenses = response.data;
                for(let i = 0;i<expenses.length;i++)
                {
                    document.getElementById('expenses').innerHTML+=`
                        <div class="transaction">
                            <div class="transaction-info">
                                <div class="transaction-icon"></div>
                                <span>${expenses[i].type}</span>
                            </div>
                            <span>${expenses[i].amount} $</span>
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