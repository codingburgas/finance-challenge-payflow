import axios from 'axios';
const apiURL = 'http://localhost:18080/api/';

document.getElementById('fetchButton').addEventListener('click', GetTests);

function GetTests()
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
                    <div class="playmentEntry">
                        <p>Paymets to: ${payments[i].paymentTo}, Amount: ${payments[i].amount}, On date: ${payments[i].paymentDate}</p>

                    </div>
                `;
            }
        }
        else
        {
            console.error(response.status);
        }
    })
    .catch(function (error) {
        console.error(error);
        document.getElementById('result').innerText = 'Error fetching data';
    });
}