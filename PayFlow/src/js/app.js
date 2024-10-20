import axios from 'axios';
const apiURL = 'http://localhost:18080/api/';

document.getElementById('fetchButton').addEventListener('click', ()=>
{
    getAllPayments();
});

document.getElementById('result').addEventListener('click', function(e) {
    if (e.target.id == 'payment-delete') {
        let paymentId = e.target.getAttribute('data-id');
        deletePayments(paymentId);
    }
});

function getAllPayments()
{
    axios.get(apiURL + 'payments/getAll')
    .then(function (response) {
        if(response.status == 200)
        {
            console.log(response.data);
            let payments = response.data;

            for(let i = 0;i<payments.length;i++)
            {
                let resultContainer = document.getElementById('result').innerHTML+=`
                    <div class="playmentEntry" id="payment-${payments[i].id}">
                        <p>Paymets to: ${payments[i].paymentTo}, Amount: ${payments[i].amount}, On date: ${payments[i].paymentDate}</p>
                        <button id="payment-delete" data-id="${payments[i].id}">Delete</button>
                    </div>
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
            document.getElementById(`payment-${id}`).remove();
            alert("Payment deleted");
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