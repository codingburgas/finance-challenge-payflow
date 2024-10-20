USE [master]
GO
CREATE DATABASE [PayFlowExample]
GO
USE [PayFlowExample]
GO
CREATE TABLE [dbo].[Payments](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[UserId] [int] NOT NULL,
	[PaymentTo] [nvarchar](265) NOT NULL,
	[PaymentDate] [datetime2](7) NOT NULL,
	[Amount] [decimal](9, 2) NOT NULL,
	[BillingAddress] [nvarchar](256) NULL,
	[ReturnedAmount] [int] NULL,
 CONSTRAINT [PK_Payments] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
