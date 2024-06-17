<template>
    <div>

        <div class="flex bg-blue-100">

            <main class="flex-1 p-4">


                <div v-if="currentTab === 'projects'">
                    <h2 class="text-2xl mb-4">Список проектов</h2>
                    <table class="min-w-full bg-white">
                        <thead class="bg-blue-300">
                            <tr>
                                <th class="w-1/3 px-4 py-2">Название</th>
                                <th class="w-1/6 px-4 py-2">Код</th>
                                <th class="w-1/6 px-4 py-2">Активный</th>
                                <th class="w-1/3 px-4 py-2 text-center">Действия</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="(project, index) in projects" :key="project.code" class="border-t">
                                <td class="px-4 py-2">{{ project.name }}</td>
                                <td class="px-4 py-2">{{ project.code }}</td>
                                <td class="px-4 py-2">{{ project.active ? 'Да' : 'Нет' }}</td>
                                <td class="px-4 py-2 text-center">
                                    <button @click="editProject(index)" class="text-blue-500 mr-2">✏️</button>
                                    <button @click="deleteProject(index)" class="text-red-500 mr-2">🗑️</button>
                                    <button @click="saveProject(index)" class="text-green-500">💾</button>
                                </td>
                            </tr>
                            <tr>
                                <td class="px-4 py-2">
                                    <input v-model="newProject.name" class="w-full px-2 py-1 border rounded" placeholder="Название" />
                                </td>
                                <td class="px-4 py-2">
                                    <input v-model="newProject.code" class="w-full px-2 py-1 border rounded" placeholder="Код" />
                                </td>
                                <td class="px-4 py-2 text-center">
                                    <input type="checkbox" v-model="newProject.active" />
                                </td>
                                <td class="px-4 py-2 text-center">
                                    <button @click="addProject" class="text-blue-500">➕</button>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </main>
        </div>
    </div>

</template>

<script>
  export default {
    data() {
      return {
        currentTab: 'projects',

        projects: [
          { name: 'Название1', code: 1, active: true },
          { name: 'Название2', code: 2, active: true },
          { name: 'Название3', code: 3, active: true },
          { name: 'Название4', code: 4, active: false },
          { name: 'Название5', code: 5, active: true },
        ],
        newProject: { name: '', code: '', active: false }
      };
    },
    methods: {
      addProject() {
        if (this.newProject.name && this.newProject.code) {
          this.projects.push({ ...this.newProject });
          this.newProject = { name: '', code: '', active: false };
        }
      },
      editProject(index) {
        this.newProject = { ...this.projects[index] };
        this.projects.splice(index, 1);
      },
      deleteProject(index) {
        this.projects.splice(index, 1);
      },
      saveProject(index) {
        this.projects.splice(index, 1, this.newProject);
        this.newProject = { name: '', code: '', active: false };
      }
    }
  };
</script>

<style scoped>
    /* Add any additional styles here */
</style>
