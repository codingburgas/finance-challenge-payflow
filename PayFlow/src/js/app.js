import axios from 'axios';
const apiURL = 'http://localhost:18080/api/';
let userId = -1;

document.getElementById('fetchButton').addEventListener('click', ()=>
{
    getAllPayments();
});

document.getElementById('result').addEventListener('click', (event) => {
    if (event.target.id == 'payment-delete') {
        let paymentId = event.target.getAttribute('data-id');
        deletePayments(paymentId);
    }
});

document.getElementById('logInForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    logIn(formJSON);
});

document.getElementById('registerForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
});

function getAllPayments()
{
    axios.get(apiURL + `payments/getByUser/${userId}`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log(response.data);
                let payments = response.data;
    
                for(let i = 0;i<payments.length;i++)
                {
                    document.getElementById('result').innerHTML+=`
                        <div class="playmentEntry" id="payment-${payments[i].id}">
                            <p>Paymets to: ${payments[i].paymentTo}, Amount: ${payments[i].amount}, On date: ${payments[i].paymentDate}</p>
                            <button id="payment-delete" data-id="${payments[i].id}">Delete</button>
                        </div>
                    `;
                }
            }
            else
            {
                document.getElementById('result').innerHTML+=`
                    <p>No results</p>
                `;
            }
        }
        else
        {
            console.log(response.status);
            alert("Payment not loaded. Error occured");
        }
    })
    .catch(function (error) {
        console.log(error);
        alert("Fatal error");
    });
}

function deletePayments(id)
{
    axios.get(apiURL + `payments/delete/${id}`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                document.getElementById(`payment-${id}`).remove();
                alert("Payment deleted");
            }
        }
        else
        {
            console.log(error);
            alert("Payment not deleted. Error occured");
        }
    })
    .catch(function (error) {
        console.log(error);
        alert("Fatal error");
    });
}

function logIn(body)
{
    axios.post(apiURL + `user/logIn`, body)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response != null)
            {
                console.log(response.data);
                if(response.data.userId != -1)
                {
                    userId = response.data.userId;
                    alert(`User logged ${userId}`);
                }
                else
                {
                    alert("Unauthorised");
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

function register(body)
{
    axios.post(apiURL + `user/register`, body)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response != null)
            {
                console.log(response.data);
                if(response.data.userId != -1)
                {
                    userId = response.data.userId;
                    alert(`User logged ${userId}`);
                }
                else
                {
                    alert("Unauthorised");
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
