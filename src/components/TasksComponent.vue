<template>
  <div>
    <div class="flex bg-blue-100">
      <main class="flex-1 p-4">
          <div v-if="currentTab === 'transactions'">
              <h2 class="text-2xl mb-4">Список проводок</h2>

              <div class="mb-4">
                  <label class="inline-flex items-center">
                      <input type="radio" class="form-radio" v-model="timeFilter" value="all" />
                      <span class="ml-2">За все время</span>
                  </label>
                  <label class="inline-flex items-center ml-6">
                      <input type="radio" class="form-radio" v-model="timeFilter" value="day" />
                      <span class="ml-2">За день недели</span>
                  </label>
                  <label class="inline-flex items-center ml-6">
                      <input type="radio" class="form-radio" v-model="timeFilter" value="month" />
                      <span class="ml-2">За месяц</span>
                  </label>
              </div>
              <div v-if="timeFilter === 'day'" class="mb-4">
                  <input type="date" v-model="selectedDate" class="form-input px-4 py-2 rounded" />
              </div>
              <table class="min-w-full bg-white">
                  <thead class="bg-blue-300">
                      <tr>
                          <th class="w-1/6 px-4 py-2">Дата</th>
                          <th class="w-1/6 px-4 py-2">Количество часов</th>
                          <th class="w-1/3 px-4 py-2">Описание</th>
                          <th class="w-1/6 px-4 py-2">Задача</th>
                          <th class="w-1/6 px-4 py-2 text-center">Действия</th>
                      </tr>
                  </thead>
                  <tbody>
                      <tr  v-for="(transaction, index) in filteredTransactions" :key="index" :class="transactionClass(transaction.hours)">
                          <td class="px-4 py-2">
                              <input type="date" v-if="editingIndex === index" v-model="editTransactionData.date" class="w-full px-2 py-1 border rounded" />
                              <span v-else>{{ transaction.date }}</span>
                          </td>
                          <td class="px-4 py-2">
                              <input v-if="editingIndex === index" v-model="editTransactionData.hours" class="w-full px-2 py-1 border rounded" />
                              <span v-else>{{ transaction.hours }}</span>
                          </td>
                          <td class="px-4 py-2">
                              <input v-if="editingIndex === index" v-model="editTransactionData.description" class="w-full px-2 py-1 border rounded" />
                              <span v-else>{{ transaction.description }}</span>
                          </td>
                          <td class="px-4 py-2">
                              <input v-if="editingIndex === index" v-model="editTransactionData.task" class="w-full px-2 py-1 border rounded" />
                              <span v-else>{{ transaction.task }}</span>
                          </td>
                          <td class="px-4 py-2 text-center">
                              <button @click="editTransaction(index)" class="text-blue-500 mr-2" v-if="editingIndex !== index">✏️</button>
                              <button @click="saveTransaction(index)" class="text-green-500 mr-2" v-if="editingIndex === index">💾</button>
                              <button @click="cancelEdit()" class="text-red-500 mr-2" v-if="editingIndex === index">✖️</button>
                              <button @click="deleteTransaction(index)" class="text-red-500">🗑️</button>
                          </td>
                      </tr>

                      <tr :class="transactionClass(newTransaction.hours)">
                          <td class="px-4 py-2">
                              <input type="date" v-model="newTransaction.date" class="w-full px-2 py-1 border rounded" placeholder="Дата" />
                          </td>
                          <td class="px-4 py-2">
                              <input v-model="newTransaction.hours" class="w-full px-2 py-1 border rounded" placeholder="Количество часов" />
                          </td>
                          <td class="px-4 py-2">
                              <input v-model="newTransaction.description" class="w-full px-2 py-1 border rounded" placeholder="Описание" />
                          </td>
                          <td class="px-4 py-2">
                              <input v-model="newTransaction.task" class="w-full px-2 py-1 border rounded" placeholder="Задача" />
                          </td>
                          <td class="px-4 py-2 text-center">
                              <button @click="addTransaction()" class="text-blue-500">➕</button>
                          </td>
                      </tr>
                  </tbody>
              </table>
              <div v-if="errorMessage" class="mt-4 text-red-500">
                  {{ errorMessage }}
              </div>
              <h2 class="text-2xl mb-4">{{trIndex}}</h2>
          </div>
      </main>
    </div>
  </div>
</template>

<script>
    export default {
        props: {
            nowIndex: {
                type: Number,
                default: 0
            },
            transactions: {
                type: Array
            }
        },
  data() {
    return {
      currentTab: 'transactions',
      timeFilter: 'all',
        selectedDate: null,
       
      newTransaction: { date: '', hours: '', description: '', task: '' },
      editingIndex: null,
      editTransactionData: { date: '', hours: '', description: '', task: '' },
      errorMessage: ''
    };
  },
  computed: {
      filteredTransactions() {
          if (this.timeFilter === 'day' && this.selectedDate) {
              return this.transactions[this.nowIndex].filter(transaction => transaction.date === this.selectedDate);
      }
      if (this.timeFilter === 'month') {
        const currentMonth = new Date().getMonth();
        const currentYear = new Date().getFullYear();
          return this.transactions[this.nowIndex].filter(transaction => {
          const transactionDate = new Date(transaction.date);
          return transactionDate.getMonth() === currentMonth && transactionDate.getFullYear() === currentYear;
        });
      }
          return this.transactions[this.nowIndex];
    }
  },
  methods: {
    validateTransactionData(transaction) {
      const currentDate = new Date().toISOString().split('T')[0];
      if (!transaction.date || !transaction.hours || !transaction.description || !transaction.task) {
        this.errorMessage = 'Все поля должны быть заполнены.';
        return false;
      }
      if (new Date(transaction.date) > new Date(currentDate)) {
        this.errorMessage = 'Дата не может быть в будущем.';
        return false;
      }
      if (isNaN(transaction.hours) || transaction.hours < 0 || transaction.hours > 24) {
        this.errorMessage = 'Количество часов должно быть числом от 0 до 24.';
        return false;
      }
      this.errorMessage = '';
      return true;
    },
      addTransaction() {
      if (this.validateTransactionData(this.newTransaction)) {
          this.transactions[this.nowIndex].push({ ...this.newTransaction });
        this.newTransaction = { date: '', hours: '', description: '', task: '' };
      }
    },
      editTransaction(index) {
      this.editingIndex = index;
          this.editTransactionData = { ...this.transactions[this.nowIndex][index] };
    },
      saveTransaction(index) {
      if (this.validateTransactionData(this.editTransactionData)) {
          this.transactions[this.nowIndex].splice(index, 1, { ...this.editTransactionData });
        this.cancelEdit();
      }
    },
      deleteTransaction(index) {
          this.transactions[this.nowIndex].splice(index, 1);
    },
    cancelEdit() {
      this.editingIndex = null;
      this.editTransactionData = { date: '', hours: '', description: '', task: '' };
      this.errorMessage = '';
    },
    transactionClass(hours) {
      if (hours < 8) return 'bg-yellow-100';
      if (hours === 8) return 'bg-green-100';
      if (hours > 8) return 'bg-red-100';
      }
  },
  watch: {
    'newTransaction.hours'(newVal) {
      this.newTransaction.hours = Number(newVal);
    },
    'editTransactionData.hours'(newVal) {
      this.editTransactionData.hours = Number(newVal);
    }
  }
};
</script>

<style scoped>
/* Add any additional styles here */
</style>
